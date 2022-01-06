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
#include <functional>
#include <stack>

// Size of the stack memory
#define MACHINE_MEMORY_SIZE 1000000000

#define STACK_MEMORY_PORTION 40 // how much of the available memory is there for the stack
#define HEAP_MEMORY_PORTION 40  // how much of the available memory is there for the heap
#define STATIC_MEMORY_PORTION 20// how much of the available memory is there for the static memory 

#define STACK_MEMORY_SIZE   MACHINE_MEMORY_SIZE / STACK_MEMORY_PORTION
#define HEAP_MEMORY_SIZE    MACHINE_MEMORY_SIZE / HEAP_MEMORY_PORTION
#define STATIC_MEMORY_SIZE  MACHINE_MEMORY_SIZE / STATIC_MEMORY_PORTION

#define WORD_SIZE 4
#define REGISTER_TYPE uint32_t // unsigned int 32 bits as register, to simulate a 32 bits machine
#define BASE "BASE"   // base special variable name
#define STACK "STACK" // stack special variable name 

#define SUCCESS 0 
#define FAIL 1

// Memory for each 
namespace TacRunner 
{
    // Forward declarations:
    class MemoryChunk;

    // Map from names to line number
    using LabelMap = std::map<std::string, uint>;

    // Map from 
    using MemoryMap = std::map<uint, MemoryChunk>;

    // Map from name of register (temporal) to its actual value
    using Registers = std::map<std::string, REGISTER_TYPE>;

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
            friend class VirtualStaticMemory;

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
                            , m_allocated_memory(0)
            { }

            friend class MemoryManager;

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
            uint write_word(REGISTER_TYPE word, uint virtual_position) {return write(virtual_position, (std::byte *) &word, WORD_SIZE); } ;

            
            /**
             * @brief Read 'count' bytes from 'virtual_position' to buffer 'bytes'
             * 
             * @param virtual_position where the memory will be read from
             * @param bytes where the memory will be stored 
             * @param count how many bytes to read
             * @return uint success status, 0 un success, 1 on failure
             */
            uint read(uint virtual_position, std::byte *bytes, size_t count);
        
            /**
             * @brief Read a word from the given 'virtual_position' into 'outword'
             * 
             * @param virtual_position where to read the word from
             * @param out_word         where to read the word value
             * @return uint success status, 0 un success, 1 on failure
             */
            inline uint read_word(uint virtual_position, REGISTER_TYPE &out_word) { return read(virtual_position, (std::byte *) &out_word, sizeof(out_word)); }

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
            std::string str(bool show_memory = false) const;

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
             * @brief Get the actual physical memory position of the given 
             *        virtual position
             * 
             * @param virtual_position position in heap position space 
             * @param out_pos actual position
             * @return uint success status, 0 on success, 1 on failure
             */
            uint mem_pos(uint virtual_position, std::byte* &out_pos) const;

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

            /**
             * @brief How much memory was allocated this far
             * 
             */
            uint64_t m_allocated_memory;
    };

    class VirtualStack
    {
        public:
        VirtualStack();

        friend class MemoryManager;

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
         * @brief Write 'count' bytes to 'virtual_position' from 'bytes' buffer
         * 
         * @param virtual_position where the data will be copied into
         * @param bytes where the data will be originally stored
         * @param count how many bytes to copy
         * @return uint success status, 0 on success, 1 on failure
         */
        uint write(uint virtual_position, const std::byte *bytes, size_t count);

        /**
         * @brief copy a word to the specified position in the stack
         * 
         * @param virtual_position where to copy the word
         * @param word word to copy 
         * @return uint success status, 0 on success, 1 on failure
         */
        inline uint write_word(uint virtual_position, REGISTER_TYPE word) {return write(virtual_position, (std::byte*) &word, sizeof(word)); }

        /**
         * @brief Read 'count' bytes from 'virtual_position' to "bytes" buffer
         * 
         * @param virtual_position where to read
         * @param bytes where to write
         * @param count how much to read
         * @return uint success status, 0 on success, 1 on failure
         */
        uint read(uint virtual_position, std::byte *bytes, size_t count);

        /**
         * @brief Read a word from 'virtual_position' to 'out_word'
         * 
         * @param virtual_position where to read
         * @param out_word where to write the word name
         * @return uint success status, 0 on success, 1 on failure
         */
        inline uint read_word(uint virtual_position, REGISTER_TYPE &out_word) {return read(virtual_position, (std::byte*) &out_word, sizeof(out_word)); }

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

        /**
         * @brief build a string representation of the stack
         * 
         * @param show_memory if should display memory content, might be a problem when there's too much memory
         *                    allocated
         * @return std::string human readable representation
         */
        std::string str(bool show_memory = false) const;

        private:

        /**
         * @brief Get the actual physical memory position of the given 
         *        virtual position
         * 
         * @param virtual_position position in stack position space 
         * @param out_pos actual position
         * @return uint success status, 0 on success, 1 on failure
         */
        uint mem_pos(uint virtual_position, std::byte* &out_pos) const;

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
        static std::byte m_memory[STACK_MEMORY_SIZE];

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

        /**
         * @brief How many read operations were performed
         * 
         */
        size_t m_read_count;

        /**
         * @brief How many write operations to stack
         * 
         */
        size_t m_write_count;
    };

    /**
     * @brief Static memory emulator. It behaves the same as the heap, but without 
     * a free operation, as the static memory stays in the program forever
     * 
     */
    class VirtualStaticMemory
    {
        public:
            /**
             * @brief Construct a new Static Memory object
             * 
             */
            VirtualStaticMemory() 
                : m_next_memory_position(1)
                , m_memory_map()
                , m_allocations_counter(0)
                , m_allocated_memory(0)
            { }

            friend class MemoryManager;

            /**
             * @brief Allocate 'size' bytes of memory in the virtual static memory, return the position if 
             *        it was possible, or 0 otherwise
             * @param size how many bytes to store 
             * @return uint virtual direction 
             */
            uint get(size_t size);

            /**
             * @brief copy 'count' bytes from 'bytes' to 'virtual_position' (in the virtual static memory)
             * 
             * @param bytes memory buffer where the memory will be copied from
             * @param count how many bytes from 'bytes' buffer to copy 
             * @param virtual_position a virtual memory address that should be a valid address inside the virtual static memory
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
            uint write_word(REGISTER_TYPE word, uint virtual_position) {return write(virtual_position, (std::byte *) &word, WORD_SIZE); } ;

            
            /**
             * @brief Read 'count' bytes from 'virtual_position' to buffer 'bytes'
             * 
             * @param virtual_position where the memory will be read from
             * @param bytes where the memory will be stored 
             * @param count how many bytes to read
             * @return uint success status, 0 un success, 1 on failure
             */
            uint read(uint virtual_position, std::byte *bytes, size_t count);
        
            /**
             * @brief Read a word from the given 'virtual_position' into 'outword'
             * 
             * @param virtual_position where to read the word from
             * @param out_word         where to write the word value
             * @return uint success status, 0 un success, 1 on failure
             */
            inline uint read_word(uint virtual_position, REGISTER_TYPE &out_word) { return read(virtual_position, (std::byte *) &out_word, sizeof(out_word)); }

            /**
             * @brief Tells if a given position is a valid memory position
             * 
             * @param virtual_position Position in the static memory
             * @return true If this is a valid allocated position
             * @return false otherwise
             */
            inline bool is_valid(uint virtual_position) const { return is_valid(virtual_position, 1); };

            /**
             * @brief Tells if a given memory segment specified by its start position
             *        and size in bytes is a valid one
             * 
             * @param virtual_position Position in the static memory
             * @param n_bytes How many bytes to check starting from 'virtual_position'
             * @return true If this is a valid allocated position
             * @return false otherwise
             */
            bool is_valid(uint virtual_position, size_t n_bytes) const;

            /**
             * @brief Create a string representation of the static memory object's state
             * 
             * @param show_memory If should show memory actual value, might be a problem when 
             *                    large segments of memory are stored
             * @return std::string string representation
             */
            std::string str(bool show_memory = false) const;

            /**
             * @brief How many memory allocations were performed 
             * 
             * @return size_t allocation count
             */
            inline size_t allocations_count() const { return m_allocations_counter; }

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
             * @brief Get the actual physical memory position of the given 
             *        virtual position
             * 
             * @param virtual_position position in static position space 
             * @param out_pos actual position
             * @return uint success status, 0 on success, 1 on failure
             */
            uint mem_pos(uint virtual_position, std::byte* &out_pos) const;

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
             * @brief how many read operations were performed
             * 
             */
            size_t m_read_counter;

            /**
             * @brief How many write operations were performed
             * 
             */
            size_t m_write_counter;

            /**
             * @brief How much memory was allocated this far
             * 
             */
            uint64_t m_allocated_memory;
    };

    /**
     * @brief Abstracts memory management.
     *        Every memory type has its own memory section in the virtual
     *        machine. But the internal memory manager objects doesn't have 
     *        a clue about it, their addresses start at 0, so this 
     *        manager object will transform total adresses into 
     *        specific adresses.
     * 
     */
    class MemoryManager
    {
        public:

        friend class TacMachine;

        /**
         * @brief Possible type of memories
         * 
         */
        enum class MemoryType
        {
            STACK_MEM,
            HEAP,
            STATIC
        };

        static std::string memory_type_to_str(MemoryType mem_type);

        public: // General functions
        /**
         * @brief Get the type of the given memory position
         * 
         * @param virtual_position 
         * @return MemoryType 
         */
        static uint type_of(uint virtual_position, MemoryManager::MemoryType &out_mem_type);

        /**
             * @brief Create a string representation of every memory manager state
             * 
             * @param show_memory If should show memory actual value, might be a problem when 
             *                    large segments of memory are stored
             * @return std::string string representation
             */
        std::string str(bool show_memory = false) const;

        /**
         * @brief Set 'count' bytes from 'bytes' to 'virtual_address', and return
         *        its status
         * 
         * @param bytes where the data will come from
         * @param count how many bytes to copy from data
         * @param virtual_address address where the data will be copied into
         * @return uint sucess status, 0 on success, 1 on failure
         */
        uint write(const std::byte *bytes, size_t count, uint virtual_address);

        /**
         * @brief Write a word into the given virtual address
         * 
         * @param word word to write
         * @param virtual_address address where to copy this word
         * @return uint sucess status, 0 on success, 1 on failure
         */
        inline uint write_word(REGISTER_TYPE word, uint virtual_address) { return write((std::byte *) &word, sizeof(word), virtual_address); }

        /**
         * @brief Write a byte into the given virtual address
         * 
         * @param byte byte to write
         * @param virtual_address address where to copy this byte
         * @return uint sucess status, 0 on success, 1 on failure
         */
        inline uint write_byte(std::byte byte, uint virtual_address) { return write(&byte, sizeof(byte), virtual_address); }

        /**
         * @brief Read "count" bytes of memory from "virtual_address" to "bytes" buffer
         * 
         * @param bytes Buffer where the data will be copied into
         * @param count how many bytes to copy 
         * @param virtual_address where to look for that data
         * @return uint sucess status, 0 on success, 1 on failure
         */
        uint read(std::byte *bytes, size_t count, uint virtual_address);

        /**
         * @brief Read a word from the specified virtual address
         * 
         * @param out_word where to store the word
         * @param virtual_address where to read the word from
         * @return uint success status, 0 on success, 1 on failure
         */
        inline uint read_word(REGISTER_TYPE& out_word, uint virtual_address) { return read((std::byte *) &out_word, sizeof(out_word), virtual_address); }

        /**
         * @brief Read a byte from the given 'virtual_position' into 'out_byte'
         * 
         * @param virtual_position where to read the byte from
         * @param out_byte         where to read the byte value
         * @return uint success status, 0 un success, 1 on failure
         */
        inline uint read_byte(std::byte &out_byte, uint virtual_position) { return read(&out_byte, sizeof(out_byte), virtual_position); }

        /**
         * @brief Move 'count' bytes from 'src' to 'dest' 
         * 
         * @param src src direction, in global address
         * @param dest destination direction, in global address
         * @param count how many bytes to copy 
         * @return uint success status, 0 on success, 1 on failure
         */
        uint move(uint src, uint dest, size_t count);

        // The following functions will return information about the memory limits
        // Every memory address of a given type TYPE is valid in the interval [TYPE_start, TYPE_end)
        static inline size_t static_start() { return 0; }
        static inline size_t static_end()   { return static_start() + STATIC_MEMORY_SIZE; }
        static inline size_t stack_start()  { return static_end(); }
        static inline size_t stack_end()    { return stack_start() + STACK_MEMORY_SIZE; }
        static inline size_t heap_start()   { return stack_end(); }
        static inline size_t heap_end()     { return heap_start() + HEAP_MEMORY_SIZE; }

        public: // Heap functions
        /**
         * @brief Allocate 'size' bytes of memory in the virtual heap memory, return the position if 
         *        it was possible, or 0 otherwise
         * @param size how many bytes to store 
         * @return uint virtual address, a valid heap address
         */
        uint malloc(size_t size) { auto x = m_heap.malloc(size); return x != 0 ? to_global(x, MemoryType::HEAP) : 0;  }

        /**
         * @brief Free the given virtual memory position, return 0 un success, 1 on failure. It should be 
         *        a valid heap address
         * 
         * @param virtual_position Position returned by malloc function, might fail if the given position
         *                         is not a one returned by malloc
         * @return uint success status, 0 on success, 1 on failure
         */
        uint free(uint virtual_position) { return m_heap.free(to_heap(virtual_position)); }

        /**
         * @brief Tells if a given memory segment specified by its start position
         *        and size in bytes is a valid one. 
         * 
         * @param virtual_position Position in the heap
         * @param n_bytes How many bytes to check starting from 'virtual_position'. 
         *                When n_bytes == 1, this function will tell you if this is a 
         *                valid address.
         * @return true If this is a valid allocated position
         * @return false otherwise
         */
        bool is_valid_heap_addr(uint virtual_position, size_t n_bytes = 1) const { return m_heap.is_valid(to_heap(virtual_position), n_bytes); };

        /**
         * @brief Get a const reference to the heap object 
         * 
         * @return  const VirtualHeap& const reference to the heap, so you 
         *          can get some data 
         */
        inline const VirtualHeap& heap() const { return m_heap; }

        public: // stack functions

        /**
         * @brief push 'count' bytes of data into the stack, from 'memory'
         * 
         * @param memory Data buffer where the data will be copied from
         * @param count How many bytes to copy from buffer
         * 
         * @return success status, 0 un success, 1 on failure
         */
        inline uint push_memory(const std::byte *memory, std::size_t count) { return m_stack.push_memory(memory, count); }

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
        inline uint pop_memory(size_t count) { return m_stack.pop_memory(count); }

        /**
         * @brief Write a word into stack memory, at the top of the stack
         * 
         * @return uint success status, 0 un success, 1 on failure
         */
        inline uint pop_word() { return m_stack.pop_memory(WORD_SIZE); }

        /**
         * @brief Stack pointer, the next available position where to store data
         * 
         * @return size_t current stack pointer
         */
        inline size_t stack_pointer() const { return m_stack.stack_pointer() + stack_start(); }

        /**
         * @brief   Set the stack pointer value. Use with caution as this 
         *          is not checked for consistency
         * @param new_sp new stack pointer to check
         * @return uint success status, 0 un success, 1 on failure
         */
        inline uint set_stack_pointer(size_t new_sp); 

        /**
         * @brief How many stack push operations were performed
         * 
         * @return size_t how many push operations were performed so far
         */
        inline size_t push_count() const { return m_stack.push_count(); }

        /**
         * @brief How many stack pop operations were performed
         * 
         * @return size_t how many pop operations were performed so far
         */
        inline size_t pop_count() const { return m_stack.pop_count(); }

        public: // Static memory section 

        /**
         * @brief Get a static memory segment
         * 
         * @param size ammount of memory to request
         * @return uint success status, 0 un success, 1 on failure
         */
        inline uint get_static_memory(size_t size) { return m_static.get(size); }

        /**
         * @brief Tells if this is a valid static memory address
         * 
         * @param addr 
         * @param n_bytes 
         * @return true 
         * @return false 
         */
        inline bool is_valid_static_static_addr(uint addr, size_t n_bytes = 1) const { return m_static.is_valid(addr, n_bytes); }

        /**
         * @brief Get a const reference to the internally managed static memory
         * 
         * @return const VirtualStaticMemory& 
         */
        inline const VirtualStaticMemory& static_memory() const { return m_static; }

        private:

        // The following functions will help you to convert from global memory to local memory
        static inline uint to_stack(uint global_addr)  { return global_addr - stack_start(); }
        static inline uint to_heap(uint global_addr)   { return global_addr - heap_start(); }
        static inline uint to_static(uint global_addr) { return global_addr - static_start(); }

        // Use this function to go from one type of memory to global memory
        static uint to_global(uint local_addr, MemoryType type);

        /**
         * @brief Find the actual position of a memory address
         * 
         * @param virtual_position Position you want to check its type and actual position
         * @param out_mem_type     Type of this memory
         * @param out_actual_pos   actual address in this memory type
         * @return uint success status, 0 on success, 1 on failure. Failure usually means that this is not a valid memory 
         *         address for whichever reason
         */
        static uint type_and_actual_pos_of(uint virtual_position, MemoryType &out_mem_type, uint &out_actual_pos);

        private:

        /**
         * @brief retrieve the actual pointer to a valid memory position
         * 
         * @param global_position virtual global position
         * @param out_actual_mem pointer to local memory
         * @return uint success status, 0 on success, 1 on failure
         */
        uint mem_pos(uint global_position, std::byte * &out_actual_mem) const;

        private:
        /**
         * @brief Stack Memory
         * 
         */
        VirtualStack m_stack;

        /**
         * @brief Heap Memory
         * 
         */
        VirtualHeap m_heap;

        /**
         * @brief Static Memory
         * 
         */
        VirtualStaticMemory m_static;
    };

    /**
     * @brief previous state in the program
     * 
     */
    struct BackUp
    {
        size_t program_counter;
        size_t stack_pointer;
        size_t frame_pointer;
        std::string next_return_reg; // (in global address)
    };

    /**
     * @brief Data representing relevant values for the actually running function
     * 
     */
    struct CallStackData
    {
        std::string func_name;
        Registers func_regs;
        uint line_num;
    };

    using CallStack = std::vector<CallStackData>;

    /**
     * @brief This class represents a Tac machine capable of running tac code
     *        as if it was a special processor for tac code
     * 
     */
    class TacMachine
    {
        public:
        /**
         * @brief Program status
         * 
         */
        enum class Status
        {
            NOT_STARTED,
            RUNNING,
            ERROR,
            FINISHED
        };

        public:
        TacMachine(Program program);

        /**
         * @brief Try to run the locally stored tac program
         * 
         */
        void run_tac_program();

        /**
         * @brief Set the register value, if it exists, overwrite it,
         * 
         * @param reg_name Register name
         * @param value    New value
         */
        void set_register(const std::string &reg_name, REGISTER_TYPE value);

        /**
         * @brief Get a register's value, and return success status
         * 
         * @param reg_name  register name 
         * @param out_value where to store return value
         * @return uint sucess status, 0 on success, 1 on failure
         */
        uint get_register(const std::string &reg_name, REGISTER_TYPE &out_value);

        /**
         * @brief Make the machine go to the specified label and continue
         *        its execution from there
         * 
         * @param label_name name of label
         * @return uint success status, 0 on success, 1 on failure
         */
        uint goto_label(std::string label_name);

        /**
         * @brief Current program position, next instruction to execute, not yet executed
         * 
         * @return uint current program position
         */
        inline uint program_counter() const { return m_program_counter; }

        /**
         * @brief Current frame position
         * 
         * @return uint frame position 
         */
        inline uint frame_pointer() const { return m_frame_pointer; }

        /**
         * @brief Current stack position, next free position
         * 
         * @return uint stack position
         */
        inline uint stack_pointer() const { return m_memory.stack_pointer(); }

        /**
         * @brief Current machine status
         * 
         * @return Status 
         */
        inline Status status() const { return m_status; }

        /**
         * @brief Return a human readable string representation of the tac machine
         * 
         * @param show_memory If should show memory of stack and heap, this might be a problem 
         *                    when there's much memory allocated
         * @return std::string human readable string
         */
        std::string str(bool show_memory = false, bool show_labels = false, bool show_registers = false, bool show_callstack = false);

        static std::string show_status(Status status);

        /**
         * @brief Return the current program position
         * 
         * @return const Tac& reference to current instruction
         */
        inline const Tac& current_instruction() const 
        { auto pc = program_counter(); return m_program[pc < m_program.size() ? pc : pc - 1]; }

        private:

        /**
         * @brief Creates a back up of the program state in the stack of states
         * 
         */
        void push_program_state(const std::string& next_return_reg);

        /**
         * @brief pop program state, setting de old state as the current state
         * 
         * @return uint success status, 0 on success, 1 else
         */
        uint pop_program_state();

        /**
         * @brief Get the last status saved
         * 
         * @return const BackUp& reference to last status saved
         */
        inline const BackUp& last_back_up() const { return m_back_ups.top(); }

        /**
         * @brief Run a single tac instruction. Successful execution will increase the program counter
         * 
         * @param tac instruction to run
         * 
         * @return uint success status, 0 on success, 1 else
         */
        uint run_tac_instruction(const Tac &tac);

        /**
         * @brief Set the instruction count to 0 for every instruction
         * 
         */
        void reset_instruction_count();

        /**
         * @brief Set the up label map object to match the stored program 
         * 
         * @return uint success status, 0 on success, 1 else
         */
        uint set_up_label_map();

        /**
         * @brief Get var's value: X == X, X[Y] == X + Y 
         * 
         * @param var variable object
         * @return uint success status, 0 on success, 1 else
         */
        uint get_var_value(const Variable &var, REGISTER_TYPE &out_value);

        /**
         * @brief Get the value of a variable: X == X, X[Y] == *(X+Y)
         * 
         * @param var variable whose value you want to access
         * @param out_value where to store variable's value
         * @return uint success status
         */
        uint access_var_value(const Variable &var, REGISTER_TYPE &out_value);

        /**
         * @brief Get the actual value of a value, it 
         * 
         * @param val value you want to poll
         * @param out_actual_val where to write actual value 
         * @return uint 
         */
        uint actual_value(const Value& val, REGISTER_TYPE& out_actual_val);

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
        size_t    m_program_counter;

        /**
         * @brief Variable indicating at which point in the program is this program
         * 
         */
        REGISTER_TYPE  m_frame_pointer;
        
        /**
         * @brief Map from labels to line numbers
         * 
         */
        LabelMap m_label_map;

        /**
         * @brief Memory management object
         * 
         */
        MemoryManager m_memory;

        /**
         * @brief How many of which instructions were found
         * 
         */
        std::map<Instr, uint64_t> m_instruction_count;

        /**
         * @brief Program status
         * 
         */
        Status m_status;

        /**
         * @brief Registers identified by name and their corresponding value
         * 
         */
        CallStack m_callstack;

        /**
         * @brief Status code on exit of the program
         * 
         */
        REGISTER_TYPE m_exit_status_code;

        /**
         * @brief Represents a previous state in the program to go back 
         *        when a return instruction is called
         * 
         */
        std::stack<BackUp> m_back_ups;

        private:
        // The following section contains functions for every instruction, every function
        // returns its success status, 0 on success, 1 on failure

        uint run_staticv(const Tac &tac);
        uint run_static_string(const Tac &tac);
        uint run_assign(const Tac &tac, char type = 'w'); // type if word ord byte, w for word, b for byte
        //  Assign functions

            /**
             * @brief Get the value of a val object as a word
             * 
             * @param val value to convert into inmediate
             * @return REGISTER_TYPE Resulting word
             */
            REGISTER_TYPE get_inmediate_from_value_w(const Value& val);
            std::byte get_inmediate_from_value_b(const Value& val);

            uint load_inmediate(const Variable& var, const Value& val, char type = 'w');     // x = 1
            uint load(const Variable& var, const Variable& val, char type = 'w');            // x = y[24];
            uint store_inmediate(const Variable& var, const Value& val, char type = 'w');    // x[10] = 24;
            uint store(const Variable& var, const Variable& val, char type = 'w');           // x[10] = y
            uint move_mem(const Variable& var, const Variable& val, char type = 'w');        // x[10] = y[24];
            uint move(const Variable& var, const Variable& val, char type = 'w');            // x = y;
        uint run_bin_op(const Tac& tac, const std::string& opr_type, bool type_matters = true); 
            // if this value is a float, and return the actual value, return success status
            uint is_float(const Value& val, uint & out_actual_val, bool &out_is_float);
            static float reg_to_float(REGISTER_TYPE val);
            static REGISTER_TYPE float_to_reg(float val);
            static int reg_to_int(REGISTER_TYPE val);
            static REGISTER_TYPE int_to_reg(int Val);
            static bool reg_to_bool(REGISTER_TYPE val);
            static REGISTER_TYPE bool_to_reg(bool Val);
            static uint add(uint l_val, uint r_val, uint& out_result) 
                { out_result = int_to_reg(reg_to_int(l_val) + reg_to_int(r_val)); return SUCCESS; }
            static uint sub(uint l_val, uint r_val, uint& out_result)
                { out_result = int_to_reg(reg_to_int(l_val) - reg_to_int(r_val)); return SUCCESS; }
            static uint mult(uint l_val, uint r_val, uint& out_result)
                { out_result = int_to_reg(reg_to_int(l_val) * reg_to_int(r_val)); return SUCCESS; }
            static uint div(uint l_val, uint r_val, uint& out_result);
            static uint mod(uint l_val, uint r_val, uint& out_result)
                { out_result = int_to_reg(reg_to_int(l_val) % reg_to_int(r_val)); return SUCCESS; }
            static uint addf(uint l_val, uint r_val, uint& out_result)
                { out_result = float_to_reg(reg_to_float(l_val) + reg_to_float(r_val)); return SUCCESS; }
            static uint subf(uint l_val, uint r_val, uint& out_result)
                { out_result = float_to_reg(reg_to_float(l_val) - reg_to_float(r_val)); return SUCCESS; }
            static uint multf(uint l_val, uint r_val, uint& out_result)
                { out_result = float_to_reg(reg_to_float(l_val) * reg_to_float(r_val)); return SUCCESS; }
            static uint divf(uint l_val, uint r_val, uint& out_result);
            static uint eq(uint l_val, uint r_val, uint& out_result)
                { out_result = l_val == r_val; return SUCCESS; }
            static uint neq(uint l_val, uint r_val, uint& out_result)
                { out_result = l_val != r_val; return SUCCESS; }
            static uint and_op(uint l_val, uint r_val, uint& out_result)
                { out_result = bool_to_reg(reg_to_bool(l_val) && reg_to_bool(r_val)); return SUCCESS; }
            static uint or_op(uint l_val, uint r_val, uint& out_result)
                { out_result = bool_to_reg(reg_to_bool(l_val) || reg_to_bool(r_val)); return SUCCESS; }
            static uint lt(uint l_val, uint r_val, uint& out_result)
                { out_result = int_to_reg(reg_to_int(l_val) < reg_to_int(r_val)); return SUCCESS; }
            static uint leq(uint l_val, uint r_val, uint& out_result)
                { out_result = int_to_reg(reg_to_int(l_val) <= reg_to_int(r_val)); return SUCCESS; }
            static uint ltf(uint l_val, uint r_val, uint& out_result)
                { out_result = reg_to_float(l_val) < reg_to_float(r_val); return SUCCESS; }
            static uint leqf(uint l_val, uint r_val, uint& out_result)
                { out_result = reg_to_float(l_val) <= reg_to_float(r_val); return SUCCESS; }
            static uint gt(uint l_val, uint r_val, uint& out_result)
                { out_result = int_to_reg(reg_to_int(l_val) > reg_to_int(r_val)); return SUCCESS; }
            static uint geq(uint l_val, uint r_val, uint& out_result)
                { out_result = int_to_reg(reg_to_int(l_val) >= reg_to_int(r_val)); return SUCCESS; }
            static uint gtf(uint l_val, uint r_val, uint& out_result)
                { out_result = reg_to_float(l_val) > reg_to_float(r_val); return SUCCESS; }
            static uint geqf(uint l_val, uint r_val, uint& out_result)
                { out_result = reg_to_float(l_val) >= reg_to_float(r_val); return SUCCESS; }
        uint run_unary_op(const Tac& tac);
        uint run_goto(const Tac& tac);
        uint run_goif(const Tac& tac, bool is_negated = false);
        uint run_malloc(const Tac& tac);
        uint run_memcpy(const Tac& tac);
        uint run_free(const Tac& tac);
        uint run_exit(const Tac& tac);
        uint run_return(const Tac& tac);
        uint run_param(const Tac& tac);
        uint run_call(const Tac& tac);
        uint run_print(const Tac& tac, char type); // type is: i for int, c for char, f for float, s for string
        uint run_read(const Tac& tac, char type); // type is: i for int, c for char, f for float, s for string
        uint run_funbegin(const Tac&tac);
        uint run_funend(const Tac&tac);
    };
}

#endif