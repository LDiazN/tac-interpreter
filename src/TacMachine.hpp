/**
 * @file TacMachine.hpp
 * @brief  Virtual machine definition running the tac
 * 
 */

#ifndef TACMACHINE_HPP
#define TACMACHINE_HPP

// Local includes 
#include "Tac.hpp"

// C++ includes
#include <array>
#include <map>
#include <cstddef> // byte type

// Size of the stack memory
#define STACK_MEMORY_SIZE 314572800

namespace TacRunner 
{
    // Map from names to line number
    using LabelMap = std::map<std::string, uint>;

    // Map from 
    using MemoryMap = std::map<uint, MemoryChunk>;

    class MemoryChunk 
    {
        public:
            /**
             * @brief Construct a new Memory Chunk object, allocates and manages memory internally, and will be freed on end
             * 
             * @param size Size in bytes for the stored memory
             * @param start_pos Where this memory chunk starts
             */
            MemoryChunk(uint size, uint start_pos);

            /**
             * @brief Destroy the Memory Chunk object, freeing its stored memory
             * 
             */
            ~MemoryChunk();

            /**
             * @brief Start position 
             * 
             * @return uint Start position in memory 
             */
            inline uint start_pos() const { return m_start_pos; }

            /**
             * @brief Size of this memory address 
             * 
             * @return uint 
             */
            inline uint size() const { return m_size; }

            /**
             * @brief String representation of this object
             * 
             * @return std::string A human readable string representing this object
             */
            std::string str() const;

            // Make virtual heap friend as that class manages a set of this object
            friend class VirtualHeap;

        private:
            /**
             * @brief Fisical memory position where the data is stored
             * 
             * @return std::byte* an actual memory position where this object's memory is stored
             */
            std::byte *memory() const { return m_memory; }

        private:
            /**
             * @brief start position in the tac machine
             * 
             */
            uint m_start_pos;

            /**
             * @brief Size in bytes
             * 
             */
            uint m_size;

            /**
             * @brief Actual memory 
             * 
             */
            std::byte *m_memory;
    };

    /**
     * @brief Implements a virtual heap memory manager
     * 
     */
    class VirtualHeap
    {
        public:
            /**
             * @brief Construct a new Heap Memory object
             * 
             */
            VirtualHeap() : m_next_memory_position(1), m_memory_map() 
            { }

            /**
             * @brief Allocate 'size' bytes of memory in the virtual heap memory, return the position if 
             *        it was possible, or 0 otherwise
             * @param size how many bytes to store 
             * @return uint virtual direction 
             */
            uint malloc(size_t size);

            /**
             * @brief Free the given virtual memory position, return 0 un success, 1 on failure
             * 
             * @param virtual_position Position returned by malloc function, might fail if the given position
             *                         is not a one returned by malloc
             * @return uint success status, 0 on success, 1 on failure
             */
            uint free(uint virtual_position);

            /**
             * @brief copy 'count' bytes from 'bytes' to 'virtual_position' (in the virtual heap)
             * 
             * @param bytes memory buffer where the memory will be copied from
             * @param count how many bytes from 'bytes' buffer to copy 
             * @param virtual_position a virtual memory address that should be a valid address inside the virtual heap
             * @return uint success status, 0 un success, 1 on failure
             */
            uint memset(std::byte * bytes, size_t count, uint virtual_position);

            /**
             * @brief Tells if a given position is a valid memory position
             * 
             * @param virtual_position Position in the heap
             * @return true If this is a valid allocated position
             * @return false otherwise
             */
            bool is_valid(uint virtual_position) const;

        private:
            /**
             * @brief Next possible position for a new memory segment
             * 
             */
            uint m_next_memory_position;

            /**
             * @brief Keep a mapping between positions and memory chunks
             * 
             */
            MemoryMap m_memory_map;
    };

    class VirtualStack
    {
        // WIP
    };

    /**
     * @brief This class represents a Tac machine capable of running tac code
     *        as if it was a special processor for tac code
     * 
     */
    class TacMachine
    {

        public:

        private:
        /**
         * @brief Program beeing run 
         * 
         */
        Program m_program;

        /**
         * @brief Variable indicating at which point in the program is this program
         * 
         */
        uint    m_program_counter;
        
        /**
         * @brief Map from labels to line numbers
         * 
         */
        LabelMap m_label_map;

        /**
         * @brief Heap memory
         * 
         */
        VirtualHeap m_heap;

    };
}

#endif