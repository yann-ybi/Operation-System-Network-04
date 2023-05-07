
/**
    @file ReplacementManager.h
    @brief A class that provides memory allocation and deallocation functionality
*/

#ifndef REPLACEMENTMANAGER_H
#define REPLACEMENTMANAGER_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>

using Handle = void*;

/**
    @brief A struct representing a block of memory
*/ 

struct Block {
    bool isFree;
    bool isLocked;
    size_t size;
    Block* next;
};

/**
    @brief A class that provides memory allocation and deallocation functionality
*/

class MemoryManager {
private:


    Block* head;
    std::vector<void*> masterPtrs;

    std::vector<Block*> smallList;
    std::vector<Block*> mediumList;
    std::vector<Block*> largeList;
    std::vector<Block*> veryLargeList;

/**

    @brief Finds a free block of the given size using the best-fit algorithm
    @param size The size of the block to allocate
    @return A pointer to the found block, or nullptr if no free block is found
*/
    Block* findFreeBlock(size_t size);

/**

    @brief Splits a block into two smaller blocks
    @param block The block to split
    @param size The size of the first block
*/
    void splitBlock(Block* block, size_t size);
/**
    @brief Merges adjacent free blocks in the linked list
*/
    void mergeBlocks();

public:
    bool verbose;
/**
 * @brief Constructs a MemoryManager object with the given size
 * @param size The size of the memory pool to allocate
 */

    MemoryManager(size_t size) {
        head = (Block*) malloc(size);
        head->isFree = true;
        head->isLocked = false;
        head->size = size - sizeof(Block);
        head->next = nullptr;
        verbose = false;

        smallList.reserve(128);
        mediumList.reserve(64);
        largeList.reserve(32);
        veryLargeList.reserve(16);
    }
/**
 * @brief Destructs a MemoryManager object, freeing all allocated memory
 */
    ~MemoryManager() {
        operator delete(head);
    }

/**
 * @brief Allocates a block of memory using the first-fit algorithm
 * @param size The size of the block to allocate
 * @return A pointer to the allocated block, or nullptr if allocation fails
 */
    void* firstFit(size_t size);
/**
 * @brief Allocates a block of memory using the best-fit algorithm
 * @param size The size of the block to allocate
 * @return A pointer to the allocated block, or nullptr if allocation fails
 */
    void* bestFit(size_t size);
/**
 * @brief Allocates a block of memory using the worst-fit algorithm
 * @param size The size of the block to allocate
 * @return A pointer to the allocated block, or nullptr if allocation fails
 */
    void* worstFit(size_t size);
/**
 * @brief Deallocates a block of memory
 * @param ptr A pointer to the block to deallocate
 */
    void deallocate(void* ptr);
/**
 * @brief Prints a visual representation of the memory pool, showing the free and allocated blocks
 */
    void printHeapMap();

/**
 * @brief Creates a handle with the given identifier and size.
 * 
 * @param n The identifier for the handle.
 * @param s The size of the block of memory to allocate.
 * @return Handle A handle to the allocated block of memory.
 */
    Handle makeHandle(int n, size_t s);

/**
 * @brief Frees the memory associated with the given handle.
 * 
 * @param h The handle to free.
 */
    void freeHandle(Handle h);


/**
 * @brief Locks the block of memory associated with the given handle.
 * 
 * @param h The handle to lock.
 */
    void lock(Handle h); 

/**
 * @brief Unlocks the block of memory associated with the given handle.
 * 
 * @param h The handle to unlock.
 */
    void unlock(Handle h); 

/**
 * @brief Defragments the memory heap, merging adjacent free blocks.
 */
    void defrag(); 

/**
 * @brief Checks the memory heap for any locked blocks and reports any found.
 */
    void checkForLockedBlocks();

/**
 * @brief Attempts to allocate a block of memory using a "smart" algorithm that selects the best fit block from a list of free blocks.
 * 
 * @param size The size of the block to allocate.
 * @return void* A pointer to the allocated block of memory.
 */
    void* smartFit(size_t size);

/**
 * @brief Frees the memory associated with the given pointer using the "smart" algorithm.
 * 
 * @param ptr A pointer to the block of memory to free.
 */
    void smartFree(void* ptr);
    
/**
 * @brief Creates a handle using the "smart" algorithm with the given identifier and size.
 * 
 * @param n The identifier for the handle.
 * @param s The size of the block of memory to allocate.
 * @return Handle A handle to the allocated block of memory.
 */

    void* smartMakeHandle(int n, size_t s);

};


#endif


