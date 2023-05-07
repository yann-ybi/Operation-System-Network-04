/**
*   @file replacementMalloc.h
*   @brief Header file for replacementMalloc library.
*/

#ifndef REPLACEMENTMALLOC_H
#define REPLACEMENTMALLOC_H


using Handle = void*;

/**
*   @brief Replacement for malloc function.
*   @param size Size of memory to allocate.
*   @return Pointer to the allocated memory block.
*/
void* myMalloc(size_t size);

/**
*   @brief Replacement for calloc function.
*   @param n Number of elements to allocate.
*   @param size Size of each element.
*   @return Pointer to the allocated memory block.
*/
void* myCalloc(size_t n, size_t size);

/**
*   @brief Replacement for free function.
*   @param ptr Pointer to the memory block to free.
*/
void myFree(void* ptr);

/**
*   @brief Enables/disables verbose output.
*   @param v True to enable verbose output, false to disable it.
*/
void verbose(bool v);

/**

*   @brief Creates a handle for a memory block.
*   @param n Arbitrary integer value to associate with the handle.
*   @param size Size of the memory block.
*   @return Handle to the memory block.
*/
void* makeHandle(int n, size_t size);

/**

*  @brief Creates a handle for a memory block using smart allocation.
*   @param n Arbitrary integer value to associate with the handle.
*   @param size Size of the memory block.
*  @return Handle to the memory block.
*/
void* smartMakeHandle(int n, size_t size);

/**
    @brief Frees a handle and the associated memory block.
    @param h Handle to the memory block.
*/
void freeHandle(Handle h);

/**
*  @brief Defragments the memory pool.
*/
void myDefrag();

/**
*   @brief Smartly allocates memory block of given size.
*   @param size Size of the memory block.
*   @return Pointer to the allocated memory block.
*/
void* smartFit(size_t size);

/**
*  @brief Frees the memory block using smart allocation.
*  @param ptr Pointer to the memory block to free.
*/
void smartFree(void* ptr);

#endif
