#include "TacMachine.hpp"
#include "Application.hpp"
#include "Tac.hpp"
#include <sstream>
#include <string.h>
#include <assert.h>

using namespace TacRunner;

// -- < Memory Chunk implementation > -----------------------
MemoryChunk::MemoryChunk(uint size, uint start_pos)
    : m_start_pos(start_pos)
    , m_size(size)
    , m_memory(new std::byte[size])
{
    if(m_memory == nullptr)
        App::error("Error creating memory chunk: could not allocate specified bytes, malloc returned NULL");
    auto mem_ptr = m_memory.get();

    memset(mem_ptr, 0, m_size);
}
    
std::string MemoryChunk::str(bool show_memory) const
{
    std::stringstream ss;
    ss  << "MemoryChunk{ position = " << m_start_pos 
        << ", size = " << m_size 
        << ", memory_addr = " << std::hex << m_memory;
    
    if (show_memory)
    {
        ss << ", memory = [";
        for (size_t i = 0; i < m_size; i++)
            ss << std::dec << (uint) m_memory[i] << ", ";
        ss << "]";
    }

    ss << " }";
    return ss.str();
}

// -- < Virtual Heap implementation > -----------------------
uint VirtualHeap::malloc(size_t size)
{
    if (size == 0)
    {
        App::warning("Trying to allocate 0 bytes of heap memory");
        return 0;
    }
    // Create new chunk for this memory
    MemoryChunk chunk(size, m_next_memory_position);
    m_next_memory_position += size;

    // Add position to memory map
    m_memory_map.insert({chunk.start_pos(), chunk});

    m_allocations_counter ++;
    m_allocated_memory += size;
    return chunk.start_pos();
}

uint VirtualHeap::free(uint virtual_position)
{
    // Find position in memory map
    auto pos = m_memory_map.find(virtual_position);
    if (pos == m_memory_map.end()) // if could not find it
    {
        // If this is an invalid position, raise an error
        stringstream ss;
        ss << "Invalid memory address to free: " << virtual_position;
        App::error(ss.str());

        return FAIL;
    }

    // Erase position if exists
    m_memory_map.erase(pos);
    m_free_counter ++;
    return SUCCESS;
}

uint VirtualHeap::write(uint virtual_position, const std::byte * bytes, size_t count)
{
    if (count == 0)
    {
        m_write_counter++;
        return SUCCESS; // nothing to do if count is 0
    }

    // Sanity check:
    if (!is_valid(virtual_position, count))
    {
        App::error("[segmentation fault] Trying to copy memory to invalid location.");
        return FAIL;
    }

    // Get iterator pointing to first pair such that pair.key > virtual_position
    auto it= m_memory_map.upper_bound(virtual_position);
    it--;

    // Safe since we know the memory chunk is valid
    auto &[_, chunk] = *it;

    // Perform write
    auto memory = chunk.memory().get();
    memcpy(memory + (virtual_position - chunk.start_pos()), bytes, count);
    m_write_counter++;
    return SUCCESS;
}

uint VirtualHeap::read(uint virtual_position, std::byte *bytes, size_t count)
{
    // check if the memory segment is a valid one
    auto valid = is_valid(virtual_position, count);
    auto last_pos = virtual_position + count - 1;
    if (!valid)
    {
        stringstream ss;
        ss << "[segmentation fault] Trying to read memory out of bounds of heap. ";
        ss << "From: " << virtual_position << " to: " << last_pos;
        ss << " (relative to heap)";
        App::error(ss.str());

        return FAIL;
    }

    // now that the memory segment is safe, we can read from it
    auto it = m_memory_map.upper_bound(virtual_position);
    assert(it != m_memory_map.begin() && "should be a valid block");

    it--;
    auto const& [start_pos, chunk] = *(it);
    auto actual_index = virtual_position - start_pos;

    // Read memory
    memcpy(bytes, chunk.memory().get() + actual_index, count);

    // Update read count 
    m_read_counter ++;
    return SUCCESS;
}

bool VirtualHeap::is_valid(uint virtual_position, size_t n_bytes) const
{

    // Every position is invalid if no memory is allocated
    if (m_memory_map.empty())
        return false;

    auto pos = m_memory_map.upper_bound(virtual_position);
    // Check if element is lower than the first one
    if (pos == m_memory_map.begin())
    {
        // Lower than the minimum
        return false;
    }

    // We have the first > virtual_position, we want the first <= virtual_position, 
    // so we substract 1 if it's not the start
    pos--; 

    auto &[_, chunk] = *pos;

    // If virtual position is greater or equal than start + size, it's an invalid position
    auto chunk_end = chunk.start_pos() + chunk.size() - 1;
    return virtual_position + n_bytes - 1 <= chunk_end;
}

std::string VirtualHeap::str(bool show_memory) const
{
    std::stringstream ss;
    ss << "[ Heap Memory ]" << std::endl;
    ss << "\t- Memory allocation count: "   << m_allocations_counter    << std::endl;
    ss << "\t- Memory free count: "         << m_free_counter           << std::endl;
    ss << "\t- Currently stored blocks: "   << m_memory_map.size()      << std::endl;
    ss << "\t- Next Free Poistion: "        << m_next_memory_position   << std::endl;
    ss << "\t- Overall allocated memory: "  << m_allocated_memory;
    
    // Print in mb if too much bytes
    if (m_allocated_memory > 1024*1024)
        ss << "(" << m_allocated_memory / (1024*1024) << " MB)" ;

    ss << std::endl;

    if (show_memory)
    {
        ss << "\t- Memory Chunks: " << std::endl;

        if (m_memory_map.size() == 0)
        ss << "\t\t<No chunks to show>" << std::endl;
        else 
            for(auto &[_, chunk] : m_memory_map)
                ss << "\t\t+ " << chunk.str(show_memory) << std::endl;
    }

    return ss.str();
}

uint VirtualHeap::mem_pos(uint virtual_position, std::byte* &out_pos) const
{
    // Try to find the nearest position inside the virtual heap
    auto it = m_memory_map.upper_bound(virtual_position);
    if( it == m_memory_map.begin() )
        return FAIL;
    
    it--;

    auto const& [_, mem_chunk] = *it;

    // check that virtual_position is inside this chunk 
    auto pos_in_chunk = virtual_position - mem_chunk.start_pos();
    
    // Check if position inside chunk is out of range
    if (pos_in_chunk >= mem_chunk.size())
        return FAIL;

    // Save position
    out_pos = mem_chunk.memory().get() + pos_in_chunk;
    return SUCCESS;
}

// -- < Virtual Stack Implementation > ------------------------------

std::byte VirtualStack::m_memory[STACK_MEMORY_SIZE];

VirtualStack::VirtualStack()
    : m_stack_pointer(0)
    , m_push_count(0)
    , m_pop_count(0)
    , m_read_count(0)
    , m_write_count(0)
{
    // Set stack memory to 0
    memset(m_memory, 0, sizeof(m_memory));
}

uint VirtualStack::push_memory(const std::byte *memory, std::size_t count)
{
    // Check if nothing to do 
    if (count == 0)
    {
        m_push_count++;
        App::warning("Trying to push 0 bytes of memory into the stack, ignoring instruction");
        return SUCCESS;
    }

    // Check if memory allocation will raise stack overflow
    if (m_stack_pointer + count >= STACK_MEMORY_SIZE)
    {
        std::stringstream ss;
        ss  << "trying to allocate " << count 
            << " bytes of memory, which will cause stack overflow. Current stack pointer: " 
            << m_stack_pointer;
        App::error(ss.str());

        return FAIL;
    }

    // copy memory to stack
    memcpy(m_memory + m_stack_pointer, memory, count);
    m_write_count++;
    // update sp
    m_stack_pointer += count;
    m_push_count++;
    
    return SUCCESS;
}

uint VirtualStack::pop_memory(size_t count)
{
    if(count > m_stack_pointer)
    {
        std::stringstream ss;
        ss  << "[stack underflow] "; 
        ss  << "Trying to free " << count << " bytes of stack memory, which will cause, more than the actual stack pointer:  ";
        ss  << m_stack_pointer << "(relative to the stack)"; 

        App::error(ss.str());
        return FAIL;
    }

    m_stack_pointer -= count;
    m_pop_count++;
    return SUCCESS;
}

uint VirtualStack::write(uint virtual_position, const std::byte *bytes, size_t count)
{
    auto last_pos = virtual_position + count - 1;

    // check if the given position is not outside the stack
    if(last_pos >= STACK_MEMORY_SIZE)
    {
        stringstream ss;
        ss << "[segmentation fault] Trying to write to a memory address that will be out of the stack";
        App::error(ss.str());
        return FAIL;
    }

    // Check if the position is outside the current stack
    if(last_pos >= m_stack_pointer)
    {
        stringstream ss;
        ss << "Writing in memory segment possibly out of the current active stack memory. ";
        ss << "Starting from 0x" << std::hex << virtual_position << " to 0x" << std::hex << last_pos;
        // App::warning(ss.str());
    }

    // Write memory 
    memcpy(m_memory + virtual_position, bytes, count);
    m_write_count++;
    return SUCCESS;
}

uint VirtualStack::read(uint virtual_position, std::byte *bytes, size_t count)
{
    auto last_pos = virtual_position + count - 1;

    // check if the given position is not outside the stack
    if(last_pos >= STACK_MEMORY_SIZE)
    {
        stringstream ss;
        ss << "[segmentation fault] Trying to read from a memory address that will be out of the stack";
        App::error(ss.str());
        return FAIL;
    }

    // Check if the position is outside the current stack
    if(last_pos >= m_stack_pointer)
    {
        stringstream ss;
        ss << "Reading memory segment possibly out of the current active stack memory. ";
        ss << "Starting from 0x" << std::hex << virtual_position << " to 0x" << std::hex << last_pos;
        App::warning(ss.str());
    }

    // Read memory 
    memcpy(bytes, m_memory + virtual_position, count);
    m_read_count++;
    return SUCCESS;
}

std::string VirtualStack::str(bool show_memory, uint stack_mem_bytes) const
{
    std::stringstream ss;
    ss << "[ Stack Memory ]"            << std::endl;
    ss << "\t- Stack Pointer (SP): "    << std::dec << m_stack_pointer  << std::endl;
    ss << "\t- Stack push count: "      << std::dec << m_push_count     << std::endl;
    ss << "\t- Stack pop count: "       << std::dec << m_pop_count      << std::endl;
    ss << "\t- Read Operations: "       << std::dec << m_read_count     << std::endl;
    ss << "\t- Write Operations: "      << std::dec << m_write_count    << std::endl;

    if (show_memory || stack_mem_bytes != 0)
    {
        ss << "\t- Memory: " << std::endl;
        ss << "[ ";
        
        auto const max_bytes_to_print = stack_mem_bytes != 0 ? stack_mem_bytes : m_stack_pointer;

        for(size_t i = 0 ;  i < max_bytes_to_print; i++)
            ss << "0x" << std::hex << (uint) m_memory[i] << ", ";

        ss << " ]" << std::endl;
    }

    return ss.str();
}

uint VirtualStack::mem_pos(uint virtual_position, std::byte* &out_pos) const
{
    out_pos = m_memory + virtual_position;
    return SUCCESS;
}

// -- < Static Memory Manager implementation > -----------------------------------------------------

uint VirtualStaticMemory::get(size_t size)
{
    if (size == 0)
    {
        App::warning("Trying to allocate 0 bytes of static memory");
        return 0;
    }
    // Create new chunk for this memory
    MemoryChunk chunk(size, m_next_memory_position);
    m_next_memory_position += size;

    // Add position to memory map
    m_memory_map.insert({chunk.start_pos(), chunk});

    m_allocations_counter ++;
    m_allocated_memory += size;
    return chunk.start_pos();
}

uint VirtualStaticMemory::write(uint virtual_position, const std::byte * bytes, size_t count)
{
    if (count == 0)
    {
        m_write_counter++;
        return SUCCESS; // nothing to do if count is 0
    }

    // Sanity check:
    if (!is_valid(virtual_position, count))
    {
        App::error("[segmentation fault] Trying to copy memory to invalid location in static memory.");
        return FAIL;
    }

    // Get iterator pointing to first pair such that pair.key > virtual_position
    auto it= m_memory_map.upper_bound(virtual_position);
    it--;

    // Safe since we know the memory chunk is valid
    auto &[_, chunk] = *it;

    // Perform write
    auto memory = chunk.memory().get();
    memcpy(memory + (virtual_position - chunk.start_pos()), bytes, count);
    m_write_counter++;
    return SUCCESS;
}

uint VirtualStaticMemory::read(uint virtual_position, std::byte *bytes, size_t count)
{
    // check if the memory segment is a valid one
    auto status = is_valid(virtual_position, count);
    auto last_pos = virtual_position + count - 1;
    if (!status)
    {
        stringstream ss;
        ss << "[segmentation fault] Trying to read memory out of bounds of heap. ";
        ss << "From: " << virtual_position << " to: " << last_pos;
        ss << " (relative to heap)";
        App::error(ss.str());

        return FAIL;
    }

    // now that the memory segment is safe, we can read from it
    auto it = m_memory_map.upper_bound(virtual_position);
    assert(it != m_memory_map.begin() && "should be a valid block");

    it--;
    auto const& [start_pos, chunk] = *(it);
    auto actual_index = virtual_position - start_pos;

    // Read memory
    memcpy(bytes, chunk.memory().get() + actual_index, count);

    // Update read count 
    m_read_counter ++;
    return SUCCESS;
}

bool VirtualStaticMemory::is_valid(uint virtual_position, size_t n_bytes) const
{

    // Every position is invalid if no memory is allocated
    if (m_memory_map.empty())
        return false;

    auto pos = m_memory_map.upper_bound(virtual_position);
    // Check if element is lower than the first one
    if (pos == m_memory_map.begin())
    {
        // Lower than the minimum
        return false;
    }

    // We have the first > virtual_position, we want the first <= virtual_position, 
    // so we substract 1 if it's not the start
    pos--; 

    auto &[_, chunk] = *pos;

    // If virtual position is greater or equal than start + size, it's an invalid position
    auto chunk_end = chunk.start_pos() + chunk.size() - 1;
    return virtual_position + n_bytes - 1 <= chunk_end;
}

std::string VirtualStaticMemory::str(bool show_memory) const
{
    std::stringstream ss;
    ss << "[ Static Memory ]" << std::endl;
    ss << "\t- Memory allocation count: "   << m_allocations_counter    << std::endl;
    ss << "\t- Currently stored blocks: "   << m_memory_map.size()      << std::endl;
    ss << "\t- Next Free Poistion: "        << m_next_memory_position   << std::endl;
    ss << "\t- Overall allocated memory: "  << m_allocated_memory;
    
    // Print in mb if too much bytes
    if (m_allocated_memory > 1024*1024)
        ss << "(" << m_allocated_memory / (1024*1024) << " MB)" ;

    ss << std::endl;

    if (show_memory)
    {
        ss << "\t- Memory Chunks: " << std::endl;

        if (m_memory_map.size() == 0)
            ss << "\t\t<No chunks to show>" << std::endl;
        else 
            for(auto &[_, chunk] : m_memory_map)
                ss << "\t\t+ " << chunk.str(show_memory) << std::endl;
    }


    return ss.str();
}

uint VirtualStaticMemory::mem_pos(uint virtual_position, std::byte* &out_pos) const
{
    // Try to find the nearest position inside the virtual heap
    auto it = m_memory_map.upper_bound(virtual_position);
    if( it == m_memory_map.begin() )
        return FAIL;
    
    it--;

    auto const& [_, mem_chunk] = *it;

    // check that virtual_position is inside this chunk 
    auto pos_in_chunk = virtual_position - mem_chunk.start_pos();
    
    // Check if position inside chunk is out of range
    if (pos_in_chunk >= mem_chunk.size())
        return FAIL;

    // Save position
    out_pos = mem_chunk.memory().get() + pos_in_chunk;
    return SUCCESS;
}

// -- < Memory Manager implementation > ------------------------------------------------------------

std::string MemoryManager::memory_type_to_str(MemoryType mem_type)
{
    switch (mem_type)
    {
    case MemoryType::STATIC:
        return "STATIC";
        break;
    
    case MemoryType::HEAP:
        return "HEAP";
        break;

    case MemoryType::STACK_MEM:
        return "STACK";
        break;
    default:
        break;
    }

    assert(false && "Invalid memory type");
    return "<invalid memory type>";
}

uint MemoryManager::type_of(uint virtual_position, MemoryManager::MemoryType &out_mem_type)
{
    uint p;
    return type_and_actual_pos_of(virtual_position, out_mem_type, p);
}

std::string MemoryManager::str(bool show_memory, uint stack_mem_bytes) const
{
    std::stringstream ss;
    ss << m_static.str(show_memory) << std::endl;
    ss << m_stack.str(show_memory, stack_mem_bytes) << std::endl;
    ss << m_heap.str(show_memory) << std::endl;

    return ss.str();
}

uint MemoryManager::write(const std::byte *bytes, size_t count, uint virtual_address)
{
    uint actual_addr;
    MemoryType type;
    auto is_valid = type_and_actual_pos_of(virtual_address, type, actual_addr);

    // Check if this position is ok
    if (is_valid == FAIL)
    {
        stringstream ss;
        ss << "Trying to write to invalid memory address: 0x" << std::hex << virtual_address;
        App::error(ss.str());
        return FAIL;
    }

    // Check if direction in last position is valid and inside the same type of memory
    uint last_pos_virtual = virtual_address + count - 1;
    MemoryType last_addr_type;
    auto last_is_valid = type_of(last_pos_virtual, last_addr_type);

    if (last_is_valid == FAIL) // if position is not valid
    {
        stringstream ss;
        ss << "Trying to write up to an invalid memory address: 0x" << std::hex << last_pos_virtual;
        ss << " starting from 0x" << std::hex << virtual_address;
        App::error(ss.str());
        return FAIL;
    }
    else if(last_addr_type != type) // if valid but in another memory type
    {
        stringstream ss;
        ss << "Trying to write up to a memory address that is valid, but in another type of memory: 0x" << std::hex << last_pos_virtual;
        ss << " starting from 0x" << std::hex << virtual_address << ". Initial position is of type " << memory_type_to_str(type);
        ss << " but last position is of type " << memory_type_to_str(last_addr_type);

        App::error(ss.str());
        return FAIL;
    }

    // Write to the right type of memory
    switch (type)
    {
    case MemoryType::HEAP:
        return m_heap.write(actual_addr, bytes, count);
        break;
    case MemoryType::STATIC:
        return m_static.write(actual_addr, bytes, count);
        break;
    case MemoryType::STACK_MEM:
        return m_stack.write(actual_addr, bytes, count);
        break;
    default:
        break;
    }

    stringstream ss;
    ss << "Unrecognized type of memory: " << static_cast<int>(type);
    App::error(ss.str());
    assert(false);
    
    return FAIL;
}

uint MemoryManager::read(std::byte *bytes, size_t count, uint virtual_address)
{
    uint actual_addr;
    MemoryType type;
    auto is_valid = type_and_actual_pos_of(virtual_address, type, actual_addr);

    // Check if this position is ok
    if (is_valid == FAIL)
    {
        stringstream ss;
        ss << "[segmentation fault] Trying to read to invalid memory address: 0x" << std::hex << virtual_address;
        App::error(ss.str());
        return FAIL;
    }

    // Check if direction in last position is valid and inside the same type of memory
    uint last_pos_virtual = virtual_address + count - 1;
    MemoryType last_addr_type;
    auto last_is_valid = type_of(last_pos_virtual, last_addr_type);

    if (last_is_valid == FAIL) // if position is not valid
    {
        stringstream ss;
        ss << "[segmentation fault] Trying to read up to an invalid memory address: 0x" << std::hex << last_pos_virtual;
        ss << " starting from 0x" << std::hex << virtual_address;
        App::error(ss.str());
        return FAIL;
    }
    else if(last_addr_type != type) // if valid but in another memory type
    {
        stringstream ss;
        ss << "[segmentation fault] Trying to read up to a memory address that is valid, but in another type of memory: " << std::hex << last_pos_virtual;
        ss << " starting from 0x" << std::hex << virtual_address << ". Initial position is of type " << memory_type_to_str(type);
        ss << " but last position is of type " << memory_type_to_str(last_addr_type);

        App::error(ss.str());
        return FAIL;
    }

    // Read from the right type of memory
    switch (type)
    {
    case MemoryType::HEAP:
        return m_heap.read(actual_addr, bytes, count);
        break;
    case MemoryType::STATIC:
        return m_static.read(actual_addr, bytes, count);
        break;
    case MemoryType::STACK_MEM:
        return m_stack.read(actual_addr, bytes, count);
        break;
    default:
        break;
    }

    stringstream ss;
    ss << "Unrecognized type of memory: " << static_cast<int>(type);
    App::error(ss.str());
    assert(false);
    
    return FAIL;
}

uint MemoryManager::move(uint src, uint dest, size_t count)
{
    // a byte buffer to perform the move operation
    std::byte * buffer = new std::byte[count];

    if (read(buffer, count, src) == FAIL)
        return FAIL;
    else
        return write(buffer, count, dest);
    
    delete buffer;
}

uint MemoryManager::set_stack_pointer(size_t new_sp)
{
    // Check that this is a valid Stack Pointer
    if( new_sp < stack_start() || new_sp >= stack_end())
    {
        stringstream ss;
        ss << "Error, memory address: 0x" << std::hex << new_sp << " is not a valid stack address";
        App::error(ss.str());
        return FAIL;
    }

    m_stack.set_stack_pointer(to_stack(new_sp));
    return SUCCESS;
}

uint MemoryManager::to_global(uint local_addr, MemoryManager::MemoryType type)
{
    switch (type)
    {
    case MemoryType::HEAP:
        return local_addr + heap_start();
        break;
    case MemoryType::STACK_MEM:
        return local_addr + stack_start();
        break;
    case MemoryType::STATIC:
        assert(local_addr >= static_start() && local_addr < static_end());
        return local_addr + static_start();
        break;
    default:
        break;
    }

    assert(false && "Unrecognized type of memory");
    return 0;
}

uint MemoryManager::type_and_actual_pos_of(uint virtual_position, MemoryManager::MemoryType &out_mem_type, uint &out_actual_pos)
{
    
    if( static_start() <= virtual_position && virtual_position < static_end())
    {
        out_mem_type = MemoryType::STATIC;
        out_actual_pos = virtual_position - static_start();
        return SUCCESS;
    }
    else if( stack_start() <= virtual_position && virtual_position < stack_end())
    {
        out_mem_type = MemoryType::STACK_MEM;
        out_actual_pos = virtual_position - stack_start();
        return SUCCESS;
    }
    else if( heap_start() <= virtual_position && virtual_position < heap_end())
    {
        out_mem_type = MemoryType::HEAP;
        out_actual_pos = virtual_position - heap_start();
        return SUCCESS;
    }

    stringstream ss;
    ss << "Memory position: 0x" << std::hex << virtual_position << " it's an invalid position, out of every kind of memory";
    App::warning(ss.str());

    return FAIL;
}

uint MemoryManager::mem_pos(uint global_position, byte * &out_actual_mem) const
{
    MemoryType type;
    uint local_position;

    if(type_and_actual_pos_of(global_position, type, local_position) == FAIL)
    {
        stringstream ss;
        ss << "Could not retrieve physical position of global position 0x" << std::hex << global_position;
        App::error(ss.str());
        return FAIL;
    }

    switch (type)
    {
    case MemoryType::STACK_MEM:
        return m_stack.mem_pos(local_position, out_actual_mem);
    case MemoryType::HEAP:
        return m_heap.mem_pos(local_position, out_actual_mem);
    case MemoryType::STATIC:
        return m_static.mem_pos(local_position, out_actual_mem);
    default:
        assert(false && "Invalid memory type");
        break;
    }

    return FAIL;
}

// -- < Tac Machine implementation > -----------------------------------

TacMachine::TacMachine(Program program)
    : m_program(program)
    , m_program_counter(0)
    , m_memory()
    , m_status(Status::NOT_STARTED)
    , m_exit_status_code(0)
{
    m_frame_pointer = stack_pointer();

    // push global scope to callstack
    m_callstack.push_back(CallStackData{"<GLOBAL SCOPE>", Registers(), 0});


    // initialize instruction counting
    reset_instruction_count();

    // Create instruction map
    if (set_up_label_map() == FAIL)
    {
        App::error("Error trying to parse labels into line numbers");
        m_status = Status::ERROR;
    }
}

void TacMachine::run_tac_program()
{
    // Expects to be ready to init 
    if (m_status != Status::NOT_STARTED)
        return;

    m_status = Status::RUNNING;
    m_program_counter = 0;
    while(m_status == Status::RUNNING)
    {
        // Check if the program finished
        if (m_program_counter == m_program.size())
        {
            m_status = Status::FINISHED;
            continue;
        }

        // Consistency checking
        assert(m_program_counter >= 0 && m_program_counter < m_program.size() && "Program counter out of bound");

        // Run a single instruction
        auto status = run_tac_instruction(m_program[m_program_counter]);

        // Check its status
        if (status == FAIL)
        {
            m_status = Status::ERROR;
            continue;
        }

        m_program_counter++;
    }
}

void TacMachine::set_register(const std::string &reg_name, REGISTER_TYPE value)
{
    // If one of the special variables, override register map assign
    if (reg_name == BASE)
    {
        m_frame_pointer = value;
        return;
    }
    else if ( reg_name == STACK)
    {
        m_memory.set_stack_pointer(static_cast<size_t>(value));
        return;
    }

    // Otherwise, set register in first stack entry
    assert(m_callstack.size() != 0);
    m_callstack.back().func_regs[reg_name] = value;
}

uint TacMachine::get_register(const std::string &reg_name, REGISTER_TYPE &out_value)
{
    // Check if register is special register
    if (reg_name == BASE)
    {
        out_value = m_frame_pointer;
        return SUCCESS;
    }
    else if(reg_name == STACK)
    {
        out_value = static_cast<REGISTER_TYPE>(m_memory.stack_pointer());
        return SUCCESS;
    }

    for(size_t i = m_callstack.size(); i --> 0;)
    {
        auto const& regs = m_callstack[i].func_regs;

        // Search for first occurence of the provided register
        auto it = regs.find(reg_name);
        if (it == regs.end()) // could not find it
            // keep searching 
            continue;
        
        auto &[_, value] = *it;
        out_value = value;
        return SUCCESS;
    }    
    
    stringstream ss;
    ss << "Trying to access invalid register: '" << reg_name << "'" << std::endl;
    App::error(ss.str());

    return FAIL;
}

uint TacMachine::goto_label(std::string label_name)
{
    auto it = m_label_map.find(label_name);

    // If could not find it 
    if (it == m_label_map.end())
    {
        stringstream ss;
        ss << "Can't jump to label '" << label_name << "', it does not exists";
        App::error(ss.str());

        return FAIL;
    }

    auto const&[_, line_num] = *it;

    // Update program counter
    m_program_counter = line_num;
    return SUCCESS;
}

void TacMachine::push_program_state(const std::string& next_return_reg)
{
    m_back_ups.push(
        BackUp
        {
            program_counter(), 
            stack_pointer(), 
            frame_pointer(), 
            next_return_reg
        }
    );
}

uint TacMachine::pop_program_state()
{
    if(m_back_ups.size() == 0)
    {
        stringstream ss;
        
        ss << "Could not restore previous program state, there's no previous program state";
        App::error(ss.str());
        return FAIL;
    }

    auto const& backup = last_back_up();
    m_program_counter = backup.program_counter;
    m_memory.set_stack_pointer(backup.stack_pointer);
    m_frame_pointer = backup.frame_pointer;

    m_back_ups.pop();

    return SUCCESS;
}

uint TacMachine::run_tac_instruction(const Tac &tac)
{

    switch (tac.instr())
    {
    case Instr::METASTATICV:
        return run_staticv(tac);
    case Instr::METASTRING:
        return run_static_string(tac);
    case Instr::METALABEL: // ignore
        return SUCCESS;
    case Instr::ASSIGNW:
        return run_assign(tac);
    case Instr::ASSIGNB:
        return run_assign(tac, 'b');
    case Instr::ADD:
        return run_bin_op(tac, "add");
    case Instr::SUB:
        return run_bin_op(tac, "sub");
    case Instr::MULT:
        return run_bin_op(tac, "mult");
    case Instr::DIV:
        return run_bin_op(tac, "div");
    case Instr::MOD:
        return run_bin_op(tac, "mod");
    case Instr::MINUS:
        return run_unary_op(tac);
    case Instr::NEG:
        return run_unary_op(tac);
    case Instr::EQ:
        return run_bin_op(tac, "eq", false);
    case Instr::NEQ:
        return run_bin_op(tac, "neq", false);
    case Instr::AND:
        return run_bin_op(tac, "and", false);
    case Instr::OR:
        return run_bin_op(tac, "or", false);
    case Instr::LT:
        return run_bin_op(tac, "lt");
    case Instr::LEQ:
        return run_bin_op(tac, "leq");
    case Instr::GT:
        return run_bin_op(tac, "gt");
    case Instr::GEQ:
        return run_bin_op(tac, "geq");
    case Instr::GOTO:
        return run_goto(tac);
    case Instr::GOIF:
        return run_goif(tac);
    case Instr::GOIFNOT:
        return run_goif(tac, true); // negated = true
    case Instr::MALLOC:
        return run_malloc(tac);
    case Instr::MEMCPY:
        return run_memcpy(tac);
    case Instr::FREE:
        return run_free(tac);
    case Instr::EXIT:
        return run_exit(tac);
    case Instr::RETURN:
        return run_return(tac);
    case Instr::PARAM:
        return run_param(tac);
    case Instr::CALL:
        return run_call(tac);
    case Instr::PRINTI:
        return run_print(tac, 'i');
    case Instr::PRINTF:
        return run_print(tac, 'f');
    case Instr::PRINT:
        return run_print(tac, 's');
    case Instr::PRINTC:
        return run_print(tac, 'c');
    case Instr::READI:
        return run_read(tac, 'i');
    case Instr::READF:
        return run_read(tac, 'f');
    case Instr::READ:
        return run_read(tac, 's');
    case Instr::READC:
        return run_read(tac, 'c');
    case Instr::FTOI:
        return run_convert(tac, 'i');
    case Instr::ITOF:
        return run_convert(tac, 'f');
    case Instr::METAFUNBEGIN:
        return run_funbegin(tac);
    case Instr::METAFUNEND:
        return run_funend(tac);
    default:
        stringstream ss;
        ss << "running instruction not yet implemented: " << tac.str();
        App::warning(ss.str());
        return SUCCESS;
        break;
    }

    return FAIL;
}

void TacMachine::reset_instruction_count()
{
    for(int int_inst = 0; int_inst != static_cast<int>(Instr::__LAST__); int_inst++)
    {
        Instr inst = static_cast<Instr>(int_inst);
        m_instruction_count[inst] = 0;
    }
}

uint TacMachine::set_up_label_map()
{
    m_label_map.clear();
    // Find labels in program
    for(size_t i = 0; i < m_program.size(); i++)
    {
        auto const &t = m_program[i];
        std::string label_name;

        if (t.instr() == Instr::METALABEL) // if label, get instruction name (first argument)
        {
            const auto &args = t.args();
            // Label accepts just one arg, its name
            assert(args.size() == 1 && "Error: An @label instruction should provide name of label"); 

            // get value of name 
            const auto &name_val = args[0];
            assert(name_val.is<std::string>() && "Error: The only argument of @label should be its name, a string");
            label_name = name_val.get<std::string>();
        }
        else if(t.instr() == Instr::METAFUNBEGIN)
        {
            const auto &args = t.args();
            assert(args.size() == 2 && "Error: @beginfun should provide only function name and stack size");

            // get value of name
            auto const &name_arg = args[0];
            assert(name_arg.is<std::string>());

            // Get function name as a label
            label_name = name_arg.get<std::string>();
        }
        else 
            continue;
        
        // Check that such label does not exists yet
        if (m_label_map.find(label_name) != m_label_map.end())
        {
            stringstream ss;
            ss << "Duplicate label: " << label_name;
            App::error(ss.str());

            return FAIL;
        }
        m_label_map[label_name] = i;
    }

    return SUCCESS;
}

uint TacMachine::get_var_value(const Variable &var, REGISTER_TYPE &out_value)
{
    REGISTER_TYPE reg_value;
    auto status = get_register(var.name, reg_value);

    // Check if getting value was successful
    if (status == FAIL)
        return FAIL;
    

    // Get index value
    Value val;
    if ( std::holds_alternative<int>(var.index))
        val = Value(std::get<int>(var.index));
    else 
        val = Value(Variable{std::get<std::string>(var.index), 0, false});
    
    REGISTER_TYPE reg;
    if(actual_value(val, reg) == FAIL)
    {
        stringstream ss;
        ss << "Can't access to actual value of " << val.str();
        App::error(ss.str());

        return FAIL;
    }

    out_value = reg_value + (var.is_access) * reg;        
    return SUCCESS;
}

uint TacMachine::access_var_value(const Variable &var, REGISTER_TYPE &out_value)
{
    // Try to get var first
    REGISTER_TYPE addr;
    auto status = get_var_value(var, addr);

    // finish if not ok
    if (status == FAIL)
        return status;

    if (var.is_access)
        // Try to access memory at that position
        return m_memory.read_word(out_value, addr);
    
    out_value = addr;
    return SUCCESS;
}

uint TacMachine::actual_value(const Value& val, REGISTER_TYPE& out_actual_val)
{
    REGISTER_TYPE reg;
    if(val.is<Variable>())
    {
        auto const &v = val.get<Variable>();
        if(access_var_value(v, reg) == FAIL)
        {
            stringstream ss;
            ss << "Could not retrieve value for " << v.str();
            App::error(ss.str());
            return FAIL;
        }
    }
    else if(!val.is<std::string>())
    {
        reg = get_inmediate_from_value_w(val);
    }
    else
    {
        App::error("Can't retrieve value of a string into a register");
        return FAIL;
    }

    out_actual_val = reg;
    return SUCCESS;
}

std::string TacMachine::str(bool show_memory, bool show_labels, bool show_registers, bool show_callstack, uint stack_mem_bytes)
{
    std::stringstream ss;
    ss << "-- << TAC MACHINE >> ----------------------------------------" << std::endl;
    ss << "- Program Counter (PC): " << m_program_counter << std::endl;
    ss << "- Frame Pointer (FP): " << m_frame_pointer << std::endl;
    ss << "- Current Instruction: " << 
        ( m_program_counter < m_program.size() ? m_program[m_program_counter].str() : "<Program Finished>")
        << std::endl;
    ss << "- Machine Status: " << show_status(m_status) << std::endl;
    ss << "- Currently active callstack: " << m_callstack.size() << std::endl;
    ss << "- Status Code: " << m_exit_status_code << std::endl;
    if (show_registers)
    {
        for (auto const& call_data : m_callstack)
        {
            ss << "\t- " << call_data.func_name;
            ss << "\t\t- Registers: " << std::endl;
            auto const& regs = call_data.func_regs;
            if (regs.empty())
                ss << "\t\t<No registers to show>";
            else
                for(auto &[name, value] : regs)
                    ss << "\t\t\t- " << name << " = 0x" << std::hex << value << std::endl;
                ss << std::endl;
        }
    }

    if(show_labels)
    {
        ss << "- Labels: " << std::endl;
        if(m_label_map.empty())
            ss << "<No labels to show>" << std::endl;
        else
        {
            for(auto &[name, line_num] : m_label_map)
                ss << "\t+ " << name << " : " << line_num << std::endl;
        }
    }

    if(show_callstack)
    {
        ss << "- Callstack: ";
        for (auto const& call : m_callstack)
            ss << "\t[ " << call.func_name << " ] at line " << call.line_num;
    }

    
    ss << m_memory.str(show_memory, stack_mem_bytes)  << std::endl;

    return ss.str();
}

std::string TacMachine::show_status(Status status)
{
    switch (status)
    {
    case Status::ERROR:
        return "ERROR";
        break;
    case Status::NOT_STARTED:
        return "NOT_STARTED";
        break;
    case Status::FINISHED:
        return "FINISHED";
        break;
    case Status::RUNNING:
        return "RUNNING";
        break;
    default:
        std::stringstream ss;
        ss << "Unrecognized program status: " << static_cast<int>(status);
        App::error(ss.str());
        break;
    }

    assert(false && "Invalid status value");

    return "INVALID STATUS VALUE";
}

// -- < Instructions code > --------------------------------------
// The folowing section contains implementation for every instruction
uint TacMachine::run_staticv(const Tac& tac)
{
    // Sanity check
    assert((tac.instr() == Instr::METASTATICV) && "Invalid instruction type");

    const auto &args = tac.args();
    assert(args.size() == 2 && "Invalid number of arguments in staticv instruction");

    // Get name
    auto const &name_val = args[0];
    assert(name_val.is<std::string>() && "Invalid type for first argument of staticv, should be its name");
    auto const &name = name_val.get<std::string>();

    if (name == BASE || name == STACK)
        App::warning("Trying to set up a special variable STACK or BASE to a static variable (????");

    // Get ammount of bytes to reserve
    auto const &bytes_arg = args[1];
    assert(bytes_arg.is<int>() && "Invalid type for secund argument of staticv, should be int");
    auto const bytes = bytes_arg.get<int>();

    // Allocate static memory for this variable
    auto mem_pos = m_memory.get_static_memory(bytes);

    if (mem_pos == 0)
    {
        stringstream ss;
        ss << "Could not allocate static memory for static variable '" << name << "'"; 
        App::error(ss.str());
        return FAIL;
    }

    // Set register value
    set_register(name, mem_pos);

    return SUCCESS;
}

uint TacMachine::run_static_string(const Tac& tac)
{
    assert(tac.instr() == Instr::METASTRING && "Invalid instruction type");

    const auto &args = tac.args();
    assert(args.size() == 2 && "Invalid number of arguments in @string instruction");

    // Get name
    auto const &name_val = args[0];
    assert(name_val.is<std::string>() && "Invalid type for first argument of @string, should be its name");
    auto const &name = name_val.get<std::string>();

    if (name == BASE || name == STACK)
        App::warning("Trying to set up a special variable STACK or BASE to a static variable (????");

    // Get string arg 
    auto const &string_arg = args[1];
    assert(string_arg.is<std::string>() && "Invalid type for secund argument of @string, should be a string");
    auto const &string = string_arg.get<std::string>();

    // Get enough memory for the string 
    auto mem_pos = m_memory.get_static_memory(string.size()+1);

    // Write string position and name to register
    set_register(name, mem_pos);

    return m_memory.write((std::byte *) string.c_str(), string.size()+1, mem_pos);
}

uint TacMachine::run_assign(const Tac& tac, char type)
{
    assert(type == 'w' || type == 'b');
    assert((tac.instr() == Instr::ASSIGNW || tac.instr() == Instr::ASSIGNB) && "Invalid instruction type");
    const auto &args = tac.args();
    assert(args.size() == 2 && "Invalid number of arguments in assign instruction");

    // get values
    const auto &lvalue_arg = args[0];
    const auto &rvalue_arg = args[1];

    // check that both types of memory are variables
    assert(lvalue_arg.is<Variable>() && "First argument of assignw should be Variable");
    assert(
            (
                rvalue_arg.is<Variable>()   || 
                rvalue_arg.is<char>()       || 
                rvalue_arg.is<int>()        || 
                rvalue_arg.is<float>()      ||
                rvalue_arg.is<bool>()
            ) && 
            "First argument of assignw should be Variable"
        );

    const Variable& lvalue = lvalue_arg.get<Variable>();
    if (rvalue_arg.is<Variable>())
    {
        const Variable& rvalue = rvalue_arg.get<Variable>();

        if (lvalue.is_access && rvalue.is_access)
            return move_mem(lvalue, rvalue, type);
        else if(lvalue.is_access)
            return store(lvalue, rvalue, type);
        else if(rvalue.is_access)
            return load(lvalue, rvalue, type);
        else 
            return move(lvalue, rvalue, type);
    }
    else if (!lvalue_arg.is<std::string>())
    {
        if (lvalue.is_access)
            return store_inmediate(lvalue, rvalue_arg, type);
        else 
            return load_inmediate(lvalue, rvalue_arg, type);
    }

    assert(false &&& "Invalid type for rvalue in assignw");
    return FAIL;
}

REGISTER_TYPE TacMachine::get_inmediate_from_value_w(const Value& val)
{
    assert(!val.is<std::string>() && !val.is<Variable>());

    REGISTER_TYPE actual_value;

    if (val.is<int>())
    {
        actual_value = (REGISTER_TYPE) val.get<int>();
    }
    else if (val.is<char>())
    {
        App::warning("Assign of char to word using assignw");
        actual_value = (REGISTER_TYPE) val.get<char>();
    }
    else if (val.is<bool>())
    {
        App::warning("Assign of bool to word using assignw");
        actual_value = (REGISTER_TYPE) val.get<bool>();
    }
    else if (val.is<float>())
    {
        // Use this union to convert float into word of 4 bytes
        union {
            float f;
            REGISTER_TYPE bytes;
        } u;
        u.f = val.get<float>();
        actual_value = u.bytes;
    }

    return actual_value;
}

std::byte TacMachine::get_inmediate_from_value_b(const Value& val)
{
    assert(!val.is<std::string>() && !val.is<Variable>());

    union
    {
        float f;
        int i;
        bool b;
        char c;
        std::byte byte;
    } converter;
    converter.i = 0;

    if (val.is<int>())
    {
        App::warning("Assign of int to byte using assignb");
        converter.i = val.get<int>();
    }
    else if (val.is<char>())
    {
        converter.c = val.get<char>();
    }
    else if (val.is<bool>())
    {
        converter.b = val.get<bool>();
    }
    else if (val.is<float>())
    {
        App::warning("Assign of float to byte using assignb");
        converter.f = val.get<float>();
    }

    return converter.byte;
}

uint TacMachine::load_inmediate(const Variable& var, const Value& val, char type)
{
    // Sanity check
    assert(!var.is_access && !val.is<std::string>() && !val.is<Variable>());

    if(type == 'w')
        set_register(var.name, get_inmediate_from_value_w(val));
    else if(type == 'b')
        set_register(var.name,(REGISTER_TYPE) get_inmediate_from_value_b(val));

    return SUCCESS;
}

uint TacMachine::load(const Variable& var, const Variable& val, char type)
{
    // Sanity check
    assert(!var.is_access && val.is_access);

    // Try to get addr of rvalue
    REGISTER_TYPE rvalue_addr;
    auto status = get_var_value(val, rvalue_addr);
    if (status == FAIL)
    {
        stringstream ss;
        ss << "Could not get address specified by 0x" << std::hex << val.str();
        App::error(ss.str());
        return FAIL;
    }
    
    // Try to get value from memory
    REGISTER_TYPE actual_rvalue;
    if (type == 'w')
    {
        status = m_memory.read_word(actual_rvalue, rvalue_addr);
    }
    else if (type == 'b')
    {
        std::byte b;
        status = m_memory.read_byte(b, rvalue_addr);
        actual_rvalue = (REGISTER_TYPE) b;
    }
    if ( status == FAIL)
    {
        stringstream ss;
        ss << "Could not read data in address 0x" << std::hex << rvalue_addr;
        App::error(ss.str());
        return FAIL;
    }


    // Set register to specified value
    set_register(var.name, actual_rvalue);
    return SUCCESS;
}

uint TacMachine::store_inmediate(const Variable& var, const Value& val, char type)
{
    // Sanity check
    assert(var.is_access && !val.is<std::string>() && !val.is<Variable>());

    // Try to get addr of lvalue
    REGISTER_TYPE lvalue_addr;
    auto status = get_var_value(var, lvalue_addr);
    if (status == FAIL)
    {
        stringstream ss;
        ss << "Could not get address specified by " << var.str();
        App::error(ss.str());
        return FAIL;
    }

    // Get value from inmediate
    if (type == 'w')
    {
        auto actual_val = get_inmediate_from_value_w(val);
        // Write value to memory
        status = m_memory.write_word(actual_val, lvalue_addr);
    }
    else if (type == 'b')
    {
        auto actual_val = get_inmediate_from_value_b(val);
        // Write value to memory
        status = m_memory.write_byte(actual_val, lvalue_addr);
    }
    else 
    {
        assert(false);
    }

    if (status == FAIL)
    {
        stringstream ss;
        ss << "Could not write value " << val.str();
        ss << " to address " << lvalue_addr << " specified by ";
        ss << var.str();
        App::error(ss.str());

        return FAIL;
    }

    return SUCCESS;
}

uint TacMachine::store(const Variable& var, const Variable& val, char type)
{
    // sanity check
    assert(var.is_access && !val.is_access);

    // Try to get addr of lvalue
    REGISTER_TYPE lvalue_addr;
    auto status = get_var_value(var, lvalue_addr);
    if (status == FAIL)
    {
        stringstream ss;
        ss << "Could not get address specified by " << var.str();
        App::error(ss.str());
        return FAIL;
    }

    // Value of val is its actual value
    REGISTER_TYPE actual_val;
    status = access_var_value(val, actual_val);
    if( status == FAIL)
    {
        stringstream ss;
        ss << "Could not get value of " << val.str();
        App::error(ss.str());

        return FAIL;
    }

    // Write word to memory
    if (type == 'w')
    {
        status = m_memory.write_word(actual_val, lvalue_addr);
    }
    else if (type == 'b')
    {
        std::byte b = ((std::byte *)&actual_val)[0]; 
        status = m_memory.write_byte(b, lvalue_addr);
    }

    if (status == FAIL)
    {
        stringstream ss;
        ss << "Could not write data specified by " << val.str();
        ss << " to memory address " << lvalue_addr << " specified by ";
        ss << var.str();

        App::error(ss.str());

        return FAIL;
    }

    return SUCCESS;
}

uint TacMachine::move_mem(const Variable& var, const Variable& val, char type)
{
    stringstream ss;
    ss << "Four Address Code detected in instruction: " << current_instruction().str();
    App::error(ss.str());

    return FAIL;
}

uint TacMachine::move(const Variable& var, const Variable& val, char type)
{
    // sanity check
    assert(!var.is_access && !val.is_access);

    // Try to get addr of lvalue
    REGISTER_TYPE rvalue;
    auto status = access_var_value(val, rvalue);
    if (status == FAIL)
    {
        stringstream ss;
        ss << "Could not get address specified by " << val.str();
        App::error(ss.str());
        return FAIL;
    }

    set_register(var.name, rvalue);
    return SUCCESS;
}

uint TacMachine::run_bin_op(const Tac& tac, const std::string& opr_type, bool type_matters)
{
    const auto &args = tac.args();
    assert(args.size() == 3 && "Invalid number of arguments in binary operation instruction");
    
    // get values
    const auto& lvalue_arg = args[0];
    const auto& l_operand_arg = args[1];
    const auto& r_operand_arg = args[2];

    // Check that lvalue is a variable only 
    assert(lvalue_arg.is<Variable>());

    // Get actual variable
    auto const &lvalue = lvalue_arg.get<Variable>();
    assert(!lvalue.is_access && "should not perform store and binary operation at the same time");

    // Get name of variables
    auto const &var_name = lvalue.name;

    // Check type matching of args
    uint l_val;
    uint r_val;
    bool l_is_float;
    bool r_is_float;


    // try to get type and value of l argument
    if(is_float(l_operand_arg, l_val, l_is_float) == FAIL)
    {
        stringstream ss; 
        ss << "could not get type of value " << l_operand_arg.str();
        ss << ". Perhaps such variable does not exists?";
        App::error(ss.str());

        return FAIL;
    }

    // try to get type and value of r argument
    if(is_float(r_operand_arg, r_val, r_is_float) == FAIL)
    {
        stringstream ss; 
        ss << "could not get type of value " << r_operand_arg.str();
        ss << ". Perhaps such variable does not exists?";
        App::error(ss.str());

        return FAIL;
    }

    // type checking
    if (type_matters && (l_is_float != r_is_float))
    {
        stringstream ss;
        ss << "Can't operate values of different types.";
        ss << " left operand is: " << (l_is_float ? "float" : "not float") << ".";
        ss << " right operand is: " << (r_is_float ? "float" : "not float") << ".";

        App::error(ss.str());
        return FAIL;
    }

    // Select operation to perform
    std::function<uint(uint,uint, uint&)> opr;
    if(opr_type == "add" && l_is_float)
        opr = addf;
    else if(opr_type == "add")
        opr = add;
    else if(opr_type == "sub" && l_is_float)
        opr = subf;
    else if(opr_type == "sub")
        opr = sub;
    else if(opr_type == "mult" && l_is_float)
        opr = multf;
    else if(opr_type == "mult")
        opr = mult;
    else if(opr_type == "div" && l_is_float)
        opr = divf;
    else if(opr_type == "div")
        opr = div;
    else if(opr_type == "mod" && l_is_float)
    {
        stringstream ss;
        ss << "Error in instruction " << tac.str();
        ss << ". mod operation not defined for float";
        App::error(ss.str());
    }
    else if (opr_type == "mod")
        opr = mod;
    else if (opr_type == "eq")
        opr = eq;
    else if (opr_type == "neq")
        opr = neq;
    else if (opr_type == "and")
        opr = and_op;
    else if (opr_type == "or")
        opr = or_op;
    else if (opr_type == "lt" && l_is_float)
        opr = ltf;
    else if (opr_type == "lt")
        opr = lt;
    else if (opr_type == "leq" && l_is_float)
        opr = leqf;
    else if (opr_type == "leq")
        opr = leq;
    else if (opr_type == "gt" && l_is_float)
        opr = gtf;
    else if (opr_type == "gt")
        opr = gt;
    else if (opr_type == "geq" && l_is_float)
        opr = geqf;
    else if (opr_type == "geq")
        opr = geq;
    else
    {
        stringstream ss;
        ss << "invalid operation type: " << opr_type;
        App::error(ss.str());
        assert(false);
    }
    uint result;
    if(opr(l_val, r_val, result) == FAIL)
    {
        stringstream ss;
        ss << "Could not perform binary operation " << tac.str();
        App::error(ss.str());
        return FAIL;
    }

    set_register(var_name, result);
    return SUCCESS;
}

uint TacMachine::is_float(const Value& val, uint &out_actual_val, bool &out_is_float)
{

    assert(!val.is<std::string>());

    union {
        float f;
        int i;
        char c;
        uint u;
    } any;

    if(val.is<float>())
    {
        any.f = val.get<float>();
        out_actual_val = any.u;
        out_is_float = true;
    }
    else if (val.is<int>())
    {
        any.i = val.get<int>();
        out_actual_val = any.u;
        out_is_float = false;
    }
    else if (val.is<char>())
    {
        any.u = 0;
        any.c = val.get<char>();
        out_actual_val = any.u;
        out_is_float = false;
    }
    else if (val.is<Variable>())
    {
        auto const& var = val.get<Variable>();
        assert(var.name.size() > 0);

        // check that var actually exists
        uint actual_val;
        if (get_var_value(var, actual_val) == FAIL)
            return FAIL;

        out_actual_val = actual_val;
        if (var.name[0] == 'f') // floats start with f
            out_is_float = true;
        else 
            out_is_float = false;
    }

    return SUCCESS;
}

float TacMachine::reg_to_float(REGISTER_TYPE val)
{
    union {
        float f;
        REGISTER_TYPE reg;
    } converter;

    converter.reg = val;
    return converter.f;
}

REGISTER_TYPE TacMachine::float_to_reg(float val)
{
    union {
        float f;
        REGISTER_TYPE reg;
    } converter;

    converter.f = val;
    return converter.reg;
}

int TacMachine::reg_to_int(REGISTER_TYPE val)
{
    union {
        int i;
        REGISTER_TYPE reg;
    } converter;

    converter.reg = val;
    return converter.i;
}

REGISTER_TYPE TacMachine::int_to_reg(int val)
{
    union {
        int i;
        REGISTER_TYPE reg;
    } converter;

    converter.i = val;
    return converter.reg;
}

bool TacMachine::reg_to_bool(REGISTER_TYPE val)
{
    union {
        bool b;
        REGISTER_TYPE reg;
    } converter;

    converter.reg = val;
    return converter.b;
}

REGISTER_TYPE TacMachine::bool_to_reg(bool val)
{
    union {
        bool b;
        REGISTER_TYPE reg;
    } converter;

    converter.b = val;
    return converter.reg;
}

uint TacMachine::div(uint l_val, uint r_val, uint& out_result)
{
    if (r_val == 0)
    {
        App::error("Division by 0");
        return FAIL;
    }
    
    out_result =  int_to_reg(reg_to_int(l_val) / reg_to_int(r_val));
    return SUCCESS;
}

uint TacMachine::divf(uint l_val, uint r_val, uint& out_result)
{
    if (r_val == 0)
    {
        App::error("Division by 0");
        return FAIL;
    }
    
    out_result =  float_to_reg(reg_to_float(l_val) / reg_to_float(r_val));
    return SUCCESS;
}

uint TacMachine::run_unary_op(const Tac& tac)
{
    const auto &args = tac.args();
    assert(args.size() == 2 && "Invalid number of arguments in unary operator instruction");

    // get value
    const auto &lvalue_arg = args[0];
    const auto &value_arg = args[1];

    // Sanity check
    assert(lvalue_arg.is<Variable>());
    assert(!value_arg.is<std::string>());

    const auto& var = lvalue_arg.get<Variable>();

    // sanity check
    assert(!var.is_access);

    // get value to negate
    REGISTER_TYPE reg;
    if(actual_value(value_arg, reg) == FAIL)
    {
        stringstream ss;
        ss << "Could not get actual value of '" << value_arg.str() << "' to perform neg operation";
        App::error(ss.str());

        return FAIL;
    }

    // Perform operation 
    if (tac.instr() == Instr::NEG)
        reg = ~reg;
    else if (tac.instr() == Instr::MINUS)
    {
        assert(var.name.size() > 0);
        if (var.name[0] == 'f')
            reg = float_to_reg(-reg_to_float(reg));
        else 
            reg = (REGISTER_TYPE) -((int) reg);
    }
    
    set_register(var.name, reg);
    return SUCCESS;    
}

uint TacMachine::run_goto(const Tac& tac)
{
    assert(tac.instr() == Instr::GOTO && "Invalid instruction type");
    const auto &args = tac.args();
    assert(args.size() == 1 && "Invalid number of arguments in goto instruction");
    // get values
    const auto &label_arg = args[0];
    assert(label_arg.is<std::string>() && "First argument of goto should be a label where to jump");
    auto const& label = label_arg.get<std::string>();
    
    return goto_label(label);
}

uint TacMachine::run_goif(const Tac& tac, bool is_negated)
{
    assert(
            (
                (tac.instr() == Instr::GOIF && !is_negated) ||
                (tac.instr() == Instr::GOIFNOT && is_negated)
            ) &&
                "Invalid instruction type"
        );
    const auto &args = tac.args();
    assert(args.size() == 2 && "Invalid number of arguments in goif instruction");

    // get args
    const auto& label_arg = args[0];
    const auto& value_arg = args[1];

    assert(label_arg.is<std::string>() && "First argument of goif should be a label where to jump");
    assert(!value_arg.is<std::string>());

    // get args values
    const auto& label = label_arg.get<std::string>();
    REGISTER_TYPE value;

    if(value_arg.is<Variable>())
    {
        const auto& var = value_arg.get<Variable>();
        if(access_var_value(var, value) == FAIL)
            return FAIL;
    }
    else
        value = get_inmediate_from_value_w(value_arg);

    if((value && !is_negated) || (!value && is_negated))
        return goto_label(label);

    return SUCCESS;
}

uint TacMachine::run_malloc(const Tac &tac)
{
    // Sanity check
    assert(tac.instr() == Instr::MALLOC && "Invalid instruction type");
    const auto &args = tac.args();
    assert(args.size() == 2 && "Invalid number of arguments in malloc instruction");

    // get values
    const auto &lvalue_arg = args[0];
    const auto &byte_count_arg = args[1];

    // check that both types of memory are variables
    assert(lvalue_arg.is<Variable>() && "First argument of malloc should be a variable where to store its value");
    assert(byte_count_arg.is<int>() && "Second argument of malloc should be int");

    auto byte_count = byte_count_arg.get<int>();
    auto const& lvalue = lvalue_arg.get<Variable>();
    
    // lvalue should not be a memory access
    assert(!lvalue.is_access);

    // Try to allocate memmory
    auto memory_addr = m_memory.malloc(byte_count);

    // Update register
    set_register(lvalue.name, memory_addr);
    
    return SUCCESS;
}

uint TacMachine::run_memcpy(const Tac& tac)
{
    // Sanity check
    assert(tac.instr() == Instr::MEMCPY && "Invalid instruction type");
    const auto &args = tac.args();
    assert(args.size() == 3 && "Invalid number of arguments in memcpy instruction");

    // memcpy dest src n
    // Try to get variable where the memory addr is stored
    const auto& dest_var_arg = args[0];
    const auto& src_var_arg= args[1];
    const auto& n_bytes_arg= args[2];

    // sanity check
    assert(dest_var_arg.is<Variable>());
    assert(src_var_arg.is<Variable>());

    // get actual values
    const auto& dest_var = dest_var_arg.get<Variable>();
    const auto& src_var  = src_var_arg.get<Variable>();

    // Get value of bytes
    uint n_bytes = 0;
    if(actual_value(n_bytes_arg, n_bytes) == FAIL)
    {
        App::error("Couldn't access to size value of memcopy instruction");
        return FAIL;
    }

    // Try to write n bytes from src to dest
    REGISTER_TYPE dest;
    if (access_var_value(dest_var, dest) == FAIL)
        return FAIL;

    REGISTER_TYPE src;
    if (access_var_value(src_var, src) == FAIL)
        return FAIL;

    // try to move memory 
    if( m_memory.move(src, dest, n_bytes) == FAIL)
    {
        stringstream ss;
        ss << "Could not move " << n_bytes << "from address 0x" << std::hex << src;
        ss << " to address " << std::hex << dest;
        App::error(ss.str());

        return FAIL;
    }

    return SUCCESS;
}

uint TacMachine::run_free(const Tac& tac)
{
    // Sanity check
    assert(tac.instr() == Instr::FREE && "Invalid instruction type");
    const auto &args = tac.args();
    assert(args.size() == 1 && "Invalid number of arguments in free instruction");

    // Try to get variable where the memory addr is stored
    const auto& var_arg = args[0];
    assert(var_arg.is<Variable>());
    auto const& var = var_arg.get<Variable>();

    REGISTER_TYPE value;
    auto status = access_var_value(var, value);

    if(status == FAIL)
    {
        stringstream ss;
        ss << "Could not free memory in variable: " << var.str();
        App::error(ss.str());
        return FAIL;
    }
    
    return m_memory.free(value);
}

uint TacMachine::run_exit(const Tac& tac)
{
    assert(tac.instr() == Instr::EXIT && "Invalid instruction type");
    const auto &args = tac.args();
    assert(args.size() == 1 && "Invalid number of arguments in exit instruction");

    // Try to get variable where the memory addr is stored
    const auto& var_arg = args[0];
    assert(var_arg.is<int>());
    const auto exit_code = var_arg.get<int>();
    m_exit_status_code = exit_code;
    m_status = Status::FINISHED;

    return SUCCESS;
}

uint TacMachine::run_return(const Tac& tac)
{
    assert(tac.instr() == Instr::RETURN && "Invalid instruction type");
    const auto &args = tac.args();
    assert(args.size() == 1 && "Invalid number of arguments in return instruction");

    // Get return value
    const auto& val_arg = args[0];
    REGISTER_TYPE reg;

    // Check for errors 
    if(actual_value(val_arg, reg) == FAIL)
    {
        stringstream ss;
        ss << "Could not get value for return instruction";
        App::error(ss.str());

        return FAIL;
    }

    auto const& back_up = last_back_up();
    
    // pop last stack
    m_callstack.pop_back();

    // Write actual value and check for errors
    set_register(back_up.next_return_reg, reg);

    // Go back to previous state
    if(pop_program_state() == FAIL)
    {
        App::error("Could not go back to previous program state while trying to return from function");
        return FAIL;
    }

    return SUCCESS;
}

uint TacMachine::run_param(const Tac& tac)
{
    assert(tac.instr() == Instr::PARAM && "Invalid instruction type");
    const auto& args = tac.args();
    assert(args.size() == 2 && "Invalid number of arguments in param instruction");
    
    const auto& lvalue_arg = args[0];
    const auto& offset = args[1];

    // lvalue := stack + offset
    REGISTER_TYPE offset_value;
    if (actual_value(offset, offset_value) == FAIL)
    {
        stringstream ss;
        ss << "Could not retrieve offset value in " << offset.str();
        App::error(ss.str());

        return FAIL;
    }

    // param x offset = x + stack() + offset
    // Store actual value in provided memory
    auto const offset_val = Value((int) (offset_value + stack_pointer())); 
    auto const assign_tac = Tac(Instr::ASSIGNW, lvalue_arg, offset_val);

    if(run_assign(assign_tac) == FAIL)
    {
        stringstream ss;
        ss << "Could not assign next param position to " << lvalue_arg.str();
        App::error(ss.str());
        return FAIL;
    }

    return SUCCESS;
}

uint TacMachine::run_call(const Tac& tac)
{
    assert(tac.instr() == Instr::CALL && "Invalid instruction type");
    const auto &args = tac.args();
    assert(args.size() == 2 && "Invalid number of arguments in call instruction");
    
    const auto& next_return_arg = args[0];
    const auto& function_name_arg = args[1];

    // Try to get actual values
    assert(next_return_arg.is<Variable>());
    assert(function_name_arg.is<std::string>());

    const auto& next_return = next_return_arg.get<Variable>();
    const auto& function_name = function_name_arg.get<std::string>();

    // Check argument consistency
    assert(!next_return.is_access);

    // perform save of current state
    push_program_state(next_return.name);

    // Go to function location
    if (goto_label(function_name) == FAIL)
    {
        stringstream ss;
        ss << "Could not go to function '" << function_name << "'";
        App::error(ss.str());

        return FAIL;
    }

    assert(m_program_counter != 0 && "Can't go back one instruction");
    m_program_counter--;

    return SUCCESS;
}

uint TacMachine::run_print(const Tac& tac, char type)
{
    union {
        float f;
        int   i;
        char  c;
    } constant;

    const auto &args = tac.args();
    assert(args.size() == 1 && "Invalid number of arguments in printx instruction");
    const auto& var_arg = args[0];

    REGISTER_TYPE val;
    if(actual_value(var_arg, val) == FAIL)
        return FAIL;

    // Print value according to type
    constant.i = val;
    stringstream ss;
    std::byte *string_pos = nullptr;

    switch (type)
    {
    case 'i':
        ss << constant.i;
        App::program_log(ss.str());
        break;
    case 'c':
        ss << constant.c;
        App::program_log(ss.str());
        break;
    case 'f':
        ss << constant.f;
        App::program_log(ss.str());
        break;
    case 's':
        if (m_memory.mem_pos(val, string_pos) == FAIL)
        {
            ss << "[segmentation fault] Can't print string at position 0x" << std::hex << val;
            ss << ", that's not a valid memory position";
            App::error(ss.str());

            return FAIL;
        }
        ss << (char *) string_pos;
        App::program_log(ss.str());
        break;
    default:
        assert(false && "Invalid type argument");
        break;
    }

    return SUCCESS;
}

uint TacMachine::run_read(const Tac& tac, char type)
{
    const auto &args = tac.args();
    assert(args.size() == 1 && "Invalid number of arguments in printx instruction");
    const auto& var_arg = args[0];

    // Check that variable is not access
    assert(var_arg.is<Variable>());

    const auto& var = var_arg.get<Variable>();
    assert(!var.is_access && "can't store and read at the same time");

    // get input
    std::string input;
    std::getline(cin, input);

    // Parse according to type:
    REGISTER_TYPE reg = 0;
    union
    {
        float f;
        char c;
        int i;
        REGISTER_TYPE reg;
    } convert_to;
    convert_to.reg = 0;

    try
    {
        switch (type)
        {
        case 'c':
            if (input.size() != 1)
                throw std::invalid_argument("invalid char");
            convert_to.c = input[0];
            reg = convert_to.reg;
            break;
        case 'i':
            convert_to.i = std::stoi(input);
            reg = convert_to.reg;
            break;
        case 'f':
            convert_to.f = std::stof(input);
            reg = convert_to.reg;
            break;
        default:
            break;
        }
    }
    catch (std::invalid_argument&)
    {
            stringstream ss;
            ss << "Could not parse argument in function " << instr_to_str(tac.instr());
            ss << ". Received: " << input;
            App::error(ss.str());
            return FAIL;
    }

    // Now save according to type 
    if (type != 's') // if scalar type
    {
        set_register(var.name, reg);
        return SUCCESS;
    }

    // Store string in address:
    uint addr;
    if(get_register(var.name, addr) == FAIL)
    {
        stringstream ss;
        ss << "Couldn't retrieve address in variable '" << var.str() << "' to store a string";
        App::error(ss.str());
        return FAIL;
    }

    if(m_memory.write((std::byte *) input.c_str(), input.size() + 1, addr) == FAIL)
    {
        stringstream ss;
        ss << "Couldn't store given string '" << input << "' in address 0x " << std::hex << addr;
        App::error(ss.str());

        return FAIL;
    }

    return SUCCESS;
}

uint TacMachine::run_convert(const Tac& tac, char t)
{
    // sanity check
    assert(tac.instr() == Instr::ITOF || tac.instr() == Instr::FTOI);
    const auto &args = tac.args();
    assert(args.size() == 2 && "Invalid number of arguments in float conversion instruction");
    auto const& var_arg = args[0];
    auto const& value_arg = args[1];

    // Parse variable where to store value
    assert(var_arg.is<Variable>());
    auto const& var = var_arg.get<Variable>();

    assert(!var.is_access);

    // Get actual value to assign
    REGISTER_TYPE value;
    if(actual_value(value_arg,value)  == FAIL)
    {
        App::error("Could not get actual value to convert");
        return FAIL;
    }

    // Check what conversion to perform
    union {
        float f;
        int i;
        REGISTER_TYPE reg;
    } converter;

    converter.reg = value;
    if (t == 'f')
    {
        int i = converter.i;
        converter.f = (float) i;
    }
    else if (t == 'i')
    {
        float f = converter.f;
        converter.i = (int) f;
    }
    else 
    {
        assert(false && "Invalid type of conversion");
    }

    // Perform assign
    set_register(var.name, converter.reg);

    return SUCCESS;
}

uint TacMachine::run_funbegin(const Tac&tac)
{
    assert(tac.instr() == Instr::METAFUNBEGIN);
    const auto &args = tac.args();
    assert(args.size() == 2 && "Invalid number of arguments in @function instruction");
    const auto& stack_size_arg = args[1];
    const auto& fun_name_arg = args[0];

    // assume stack size is int
    assert(stack_size_arg.is<int>());
    auto stack_size = stack_size_arg.get<int>();

    // assume fun_name_arg is string
    assert(fun_name_arg.is<std::string>());
    auto const& fun_name = fun_name_arg.get<std::string>();

    m_frame_pointer = stack_pointer();
    m_memory.set_stack_pointer(stack_pointer() + stack_size);

    // Push current callstack
    m_callstack.push_back(CallStackData{fun_name, Registers(), frame_pointer()});

    return SUCCESS;
}

uint TacMachine::run_funend(const Tac& tac)
{
    assert(tac.instr() == Instr::METAFUNEND);

    // return previous state

    if(pop_program_state() == FAIL)
    {
        App::error("Could not go back to previous position after finishing a function");
        return FAIL;
    }

    m_callstack.pop_back();
    return SUCCESS;
}   