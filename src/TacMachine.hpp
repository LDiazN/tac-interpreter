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
#include <memory>

// Size of the stack memory
#define STACK_MEMORY_SIZE 314572800
#define WORD_SIZE 4
#define REGISTER_TYPE uint32_t

namespace TacRunner 
{
    // Forward declarations:
    class MemoryChunk;

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
            std::string str(bool show_memory = true) const;

            // Make virtual heap friend as that class manages a set of this object
            friend class VirtualHeap;

        private:
            /**
             * @brief Fisical memory position where the data is stored
             * 
             * @return std::byte* an actual memory position where this object's memory is stored
             */
            std::shared_ptr<std::byte []> memory() const { return m_memory; }

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
            std::shared_ptr<std::byte []> m_memory;
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
            VirtualHeap()   : m_next_memory_position(1)
                            , m_memory_map()
                            , m_allocations_counter(0)
                            , m_free_counter(0)
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
            uint write(uint virtual_position, const std::byte * bytes, size_t count);

            /**
             * @brief Try to write a word into the specified location
             * 
             * @param word Word to write
             * @param virtual_position where to write the word 
             * @return uint status: 0 un success, 1 on failure
             */
            uint write_word(REGISTER_TYPE word, uint virtual_position);

            /**
             * @brief Tells if a given position is a valid memory position
             * 
             * @param virtual_position Position in the heap
             * @return true If this is a valid allocated position
             * @return false otherwise
             */
            inline bool is_valid(uint virtual_position) const { return is_valid(virtual_position, 1); };

            /**
             * @brief Tells if a given memory segment specified by its start position
             *        and size in bytes is a valid one
             * 
             * @param virtual_position Position in the heap
             * @param n_bytes How many bytes to check starting from 'virtual_position'
             * @return true If this is a valid allocated position
             * @return false otherwise
             */
            bool is_valid(uint virtual_position, size_t n_bytes) const;

            /**
             * @brief Create a string representation of the heap object's state
             * 
             * @param show_memory If should show memory actual value, might be a problem when 
             *                    large segments of memory are stored
             * @return std::string string representation
             */
            std::string str(bool show_memory = false);

            /**
             * @brief How many memory allocations were performed 
             * 
             * @return size_t allocation count
             */
            inline size_t allocations_count() const { return m_allocations_counter; }

            /**
             * @brief How many memory free were performed 
             * 
             * @return size_t allocation count
             */
            inline size_t free_count() const { return m_free_counter; }

            /**
             * @brief How many memory read operations were performed 
             * 
             * @return size_t allocation count
             */
            inline size_t read_count() const { return m_read_counter; }

            /**
             * @brief How many memory write operations were performed 
             * 
             * @return size_t allocation count
             */
            inline size_t write_count() const { return m_read_counter; }

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

            /**
             * @brief How many memory allocations were performed 
             * 
             */
            size_t m_allocations_counter;

            /**
             * @brief How many memory free were performed 
             * 
             */
            size_t m_free_counter;

            /**
             * @brief how many read operations were performed
             * 
             */
            size_t m_read_counter;

            /**
             * @brief How many write operations were performed
             * 
             */
            size_t m_write_counter;
    };

    class VirtualStack
    {
        public:

        /**
         * @brief push 'count' bytes of data into the stack, from 'memory'
         * 
         * @param memory Data buffer where the data will be copied from
         * @param count How many bytes to copy from buffer
         * 
         * @return success status, 0 un success, 1 on failure
         */
        uint push_memory(const std::byte *memory, std::size_t count);

        /**
         * @brief Try to write a word in the top of the stack 
         * 
         * @param word word to write
         * @return uint value to push 
         */
        inline uint push_word(REGISTER_TYPE word) { return push_memory((std::byte *) &word, WORD_SIZE); }

        /**
         * @brief pop 'count' bytes of memory from the stack
         * 
         * @param count how much memory to pop
         * 
         * @return success status, 0 un success, 1 on failure
         */
        uint pop_memory(size_t count);

        /**
         * @brief Write a word into stack memory, at the top of the stack
         * 
         * @return uint 
         */
        inline uint pop_word() { return pop_memory(WORD_SIZE); }

        /**
         * @brief Stack pointer, the next available position where to store data
         * 
         * @return size_t current stack pointer
         */
        inline size_t stack_pointer() const { return m_stack_pointer; }

        /**
         * @brief   Set the stack pointer value. Use with caution as this 
         *          is not checked for consistency
         * @param new_sp new stack pointer to check
         */
        inline void set_stack_pointer(size_t new_sp) { m_stack_pointer = new_sp; } 

        /**
         * @brief How many stack push operations were performed
         * 
         * @return size_t how many push operations were performed so far
         */
        inline size_t push_count() const { return m_push_count; }

        /**
         * @brief How many stack pop operations were performed
         * 
         * @return size_t how many pop operations were performed so far
         */
        inline size_t pop_count() const { return m_pop_count; }

        private:
        /**
         * @brief Current stack pointer, the next available position where to store data
         * 
         */
        size_t m_stack_pointer;

        /**
         * @brief Memory Buffer
         * 
         */
        std::byte m_memory[STACK_MEMORY_SIZE];

        /**
         * @brief How many stack push operations were performed
         * 
         */
        size_t m_push_count;

        /**
         * @brief How many stack pop operations were performed
         * 
         */
        size_t m_pop_count;
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