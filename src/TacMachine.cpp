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
        App::error("Trying to copy memory to invalid location.");
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

uint VirtualHeap::write_word(REGISTER_TYPE word, uint virtual_position)
{   

    stringstream ss;
    ss << "About to write a word to position: " << virtual_position;
    App::trace(ss.str());
    
    return write(virtual_position, (std::byte *) &word, WORD_SIZE);
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

    ss << "\t- Memory Chunks: " << std::endl;

    for(auto &[_, chunk] : m_memory_map)
        ss << "\t\t+ " << chunk.str(show_memory) << std::endl;

    return ss.str();
}

// -- < Virtual Stack Implementation > ------------------------------

std::byte VirtualStack::m_memory[STACK_MEMORY_SIZE];

VirtualStack::VirtualStack()
    : m_stack_pointer(0)
    , m_push_count(0)
    , m_pop_count(0)
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
        ss  << "Trying to free " << count << " bytes of memory, which will cause "
            << "a stack underflow exception";

        return FAIL;
    }

    m_stack_pointer -= count;
    m_pop_count++;
    return SUCCESS;
}

uint VirtualStack::write(uint virtual_position, std::byte *bytes, size_t count)
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
        ss << "Starting from " << std::hex << virtual_position << " to " << std::hex << last_pos;
        App::warning(ss.str());
    }

    // Write memory 
    memcpy(m_memory, bytes, count);
    return SUCCESS;
}

std::string VirtualStack::str(bool show_memory) const
{
    std::stringstream ss;
    ss << "[ Stack Memory ]"            << std::endl;
    ss << "\t- Stack Pointer (SP): "    << std::dec << m_stack_pointer  << std::endl;
    ss << "\t- Stack push count: "      << std::dec << m_push_count     << std::endl;
    ss << "\t- Stack pop count: "       << std::dec << m_pop_count      << std::endl;
    
    if (show_memory)
    {
        ss << "\t- Memory: " << std::endl;
        ss << "[ ";
        for(size_t i = 0 ;  i < m_stack_pointer; i++)
            ss << std::hex << (uint) m_memory[i] << ", ";

        ss << " ]" << std::endl;
    }

    return ss.str();
}

// -- < Memory Manager implementation >

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
    return "<invalid memory type>"
}

uint MemoryManager::type_of(uint virtual_position, MemoryManager::MemoryType &out_mem_type)
{
    uint p;
    return type_and_actual_pos_of(virtual_position, out_mem_type, p);
}

std::string MemoryManager::str(bool show_memory = false) const
{
    std::stringstream ss;

    ss << m_stack.str() << std::endl;
    ss << m_heap.str() << std::endl;

    return ss.str();
}

uint MemoryManager::write_memory(std::byte *bytes, size_t count, uint virtual_address)
{
    uint actual_addr;
    MemoryType type;
    auto is_valid = type_and_actual_pos_of(virtual_address, type, actual_addr);
    


    // Check if this position is ok
    if (is_valid == FAIL)
    {
        stringstream ss;
        ss << "Trying to write to invalid memory address: " << std::hex << virtual_address;
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
        ss << "Trying to write up to an invalid memory address: " << std::hex << last_pos_virtual;
        ss << " starting from " << std::hex << virtual_address;
        App::error(ss.str());
        return FAIL;
    }
    else if(last_addr_type != type) // if valid but in another memory type
    {
        stringstream ss;
        ss << "Trying to write up to a memory address that is valid, but in another type of memory: " << std::hex << last_pos_virtual;
        ss << " starting from " << std::hex << virtual_address << ". Initial position is of type " << memory_type_to_str(type);
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
        App::warning("writing to static memory still WIP");
        return SUCCESS;
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

uint MemoryManager::type_and_actual_pos_of(uint virtual_position, MemoryManager::MemoryType &out_mem_type, uint &out_actual_pos)
{
    auto static_start = 0;
    auto static_end = static_start + STATIC_MEMORY_SIZE;
    auto stack_start = static_end;
    auto stack_end = stack_start + STACK_MEMORY_SIZE;
    auto heap_start = stack_end;
    auto heap_end = heap_start + HEAP_MEMORY_SIZE;

    if( static_start <= virtual_position && virtual_position < static_end)
    {
        out_mem_type = MemoryType::STATIC;
        virtual_position = virtual_position - static_start;
        return SUCCESS;
    }
    else if( stack_start <= virtual_position && virtual_position < stack_end)
    {
        out_mem_type = MemoryType::STACK_MEM;
        virtual_position = virtual_position - stack_start;
        return SUCCESS;
    }
    else if( heap_start <= virtual_position && virtual_position < heap_end)
    {
        out_mem_type = MemoryType::HEAP;
        virtual_position = virtual_position - heap_start;
        return SUCCESS;
    }

    stringstream ss;
    ss << "Memory position: " << std::hex << virtual_position << " it's an invalid position, out of every kind of memory";
    App::warning(ss.str());

    return FAIL;
}

// -- < Tac Machine implementation > -----------------------------------

TacMachine::TacMachine(Program program)
    : m_program(program)
    , m_program_counter(0)
    , m_frame_pointer(0)
    , m_heap()
    , m_stack()
    , m_status(Status::NOT_STARTED)
    , m_registers()
{
    // initialize instruction counting
    reset_instruction_count();

    // Create instruction map
    set_up_label_map();
}

void TacMachine::run_tac_program()
{
    m_status = Status::RUNNING;
    m_program_counter = 0;
    while(m_status != Status::FINISHED)
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
        run_tac_instruction(m_program[m_program_counter]);
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
        m_stack.set_stack_pointer(static_cast<size_t>(value));
        return;
    }

    m_registers[reg_name] = value;
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
        out_value = static_cast<REGISTER_TYPE>(m_stack.stack_pointer());
        return SUCCESS;
    }

    auto it = m_registers.find(reg_name);
    if (it == m_registers.end()) // could not find it
    {
        stringstream ss;
        ss << "Trying to access invalid register: '" << reg_name << "'" << std::endl;
        App::error(ss.str());

        return FAIL;
    }

    auto &[_, value] = *it;

    return value;
}

uint TacMachine::run_tac_instruction(const Tac &tac)
{

    switch (tac.instr())
    {
    case Instr::METASTATICV:
        return run_staticv(tac);
        break;
    
    default:
        stringstream ss;
        ss << "running instruction: " << tac.str();
        App::warning(ss.str());
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

void TacMachine::set_up_label_map()
{
    m_label_map.clear();
    // Find labels in program
    for(size_t i = 0; i < m_program.size(); i++)
    {
        auto const &t = m_program[i];
        if (t.instr() == Instr::METALABEL) // if label, get instruction name (first argument)
        {
            const auto &args = t.args();
            // Label accepts just one arg, its name
            assert(args.size() == 1 && "Error: An @label instruction should provide name of label"); 

            // get value of name 
            const auto &name_val = args[0];
            assert(name_val.is<std::string>() && "Error: The only argument of @label should be its name, a string");
            const auto &name = name_val.get<std::string>();

            m_label_map[name] = i;
        }
    }
}

std::string TacMachine::str(bool show_memory, bool show_labels, bool show_registers)
{
    std::stringstream ss;
    ss << "-- << TAC MACHINE >> ----------------------------------------" << std::endl;
    ss << "- Program Counter (PC): " << m_program_counter << std::endl;
    ss << "- Frame Pointer (FP): " << m_frame_pointer << std::endl;
    ss << "- Current Instruction: " << m_program[m_program_counter].str() << std::endl;
    ss << "- Program Status: " << show_status(m_status) << std::endl;
    ss << "- Currently active registers: " << m_registers.size() << std::endl;

    if (show_registers)
    {
        ss << "- Registers: " << std::endl;
        for(auto &[name, value] : m_registers)
            ss << "\t- " << name << " = " << std::hex << value;
        ss << std::endl;
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

    ss << m_stack.str() << std::endl;
    ss << m_heap.str()  << std::endl;

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

    // Get Value
    App::warning("Función WIP, aún tengo que hacer un manejador de memoria estática");

    return SUCCESS;
}