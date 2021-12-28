#include "TacMachine.hpp"
#include "Application.hpp"
#include <sstream>
#include <string.h>

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

std::string MemoryChunk::str() const
{
    std::stringstream ss;
    ss  << "MemoryChunk{ position = " << m_start_pos 
        << ", size = " << m_size 
        << ", memory = " << std::hex << m_memory 
        << " }";

    return ss.str();
}

// -- < Virtual Heap implementation > -----------------------
uint VirtualHeap::malloc(size_t size)
{
    // Create new chunk for this memory
    MemoryChunk chunk(size, m_next_memory_position);
    m_next_memory_position += size;

    // Add position to memory map
    m_memory_map.insert({chunk.start_pos(), chunk});

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
    return SUCCESS;
}

uint VirtualHeap::memcopy(uint virtual_position, const std::byte * bytes, size_t count)
{
    if (count == 0)
        return SUCCESS; // nothing to do if count is 0

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

    // Perform memcopy
    auto memory = chunk.memory().get();
    memcpy(memory, bytes, count);
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