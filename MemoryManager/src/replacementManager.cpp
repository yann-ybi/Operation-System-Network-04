#include <vector>
#include <iostream>
#include "replacementManager.h"
#include "heapSize.h"


void* MemoryManager::firstFit(size_t size) {
    Block* current = head;
    while (current != nullptr) {
        if (current->isFree && current->size >= size) {
            if (current->size - size >= sizeof(Block)) {
                Block* new_block = (Block*) ((char*) current + sizeof(Block) + size);
                new_block->isFree = true;
                new_block->size = current->size - size - sizeof(Block);
                new_block->next = current->next;
                current->next = new_block;
            }
            current->isFree = false;
            current->size = size;
            if (verbose) { printHeapMap(); }
            return (void*) ((char*) current + sizeof(Block));
        }
        current = current->next;
    }
    if (verbose) { printHeapMap(); }
    return nullptr;
}

void* MemoryManager::bestFit(size_t size) {
    Block* current = head;
    Block* best_fit = nullptr;
    while (current != nullptr) {
        if (current->isFree && current->size >= size) {
            if (best_fit == nullptr || current->size < best_fit->size) {
                best_fit = current;
            }
        }
        current = current->next;
    }
    if (best_fit != nullptr) {
        if (best_fit->size - size >= sizeof(Block)) {
            Block* new_block = (Block*) ((char*) best_fit + sizeof(Block) + size);
            new_block->isFree = true;
            new_block->size = best_fit->size - size - sizeof(Block);
            new_block->next = best_fit->next;
            best_fit->next = new_block;
        }
        best_fit->isFree = false;
        best_fit->size = size;
        if (verbose) { printHeapMap(); }
        return (void*) ((char*) best_fit + sizeof(Block));
    }
    if (verbose) { printHeapMap(); }
    return nullptr;
}

void* MemoryManager::worstFit(size_t size) {
    Block* current = head;
    Block* worst_fit = nullptr;
    while (current != nullptr) {
        if (current->isFree && current->size >= size) {
            if (worst_fit == nullptr || current->size > worst_fit->size) {
                worst_fit = current;
            }
        }
        current = current->next;
    }
    if (worst_fit != nullptr) {
        if (worst_fit->size - size >= sizeof(Block)) {
            Block* new_block = (Block*) ((char*) worst_fit + sizeof(Block) + size);
            new_block->isFree = true;
            new_block->size = worst_fit->size - size - sizeof(Block);
            new_block->next = worst_fit->next;
            worst_fit->next = new_block;
        }
        worst_fit->isFree = false;
        worst_fit->size = size;
        if (verbose) { printHeapMap(); }
        return (void*) ((char*) worst_fit + sizeof(Block));
    }
    if (verbose) { printHeapMap(); }
    return nullptr;
}


void MemoryManager::deallocate(void* ptr) {
    Block* current = head;
    while (current != nullptr) {
        if ((void*) ((char*) current + sizeof(Block)) == ptr) {
            current->isFree = true;
            if (current->next != nullptr && current->next->isFree) {
                current->size += sizeof(Block) + current->next->size;
                current->next = current->next->next;
            }
            if (current != head && current->isFree && current->next == nullptr) {
                Block* previous = head;
                while (previous->next != current) {
                    previous = previous->next;
                }
                previous->next = nullptr;
            }
            break;
        }
        current = current->next;
    }
    if (current == nullptr) {
        std::cerr << "ERROR: Attempted to free an unallocated pointer.\n";
        return;
    }
    if (verbose) { printHeapMap(); }
}

void MemoryManager::printHeapMap() {
    std::cout << "Printing heap Map  addr  size  offst  status: " << std::endl;

    Block* current = head;
    size_t offset = 0;
    while (current != nullptr) {
        std::cout << "  - " << current << " - " <<  current->size << " - " << offset << " - " << (current->isFree ? "Free" : "Allocated") << std::endl;
        offset += sizeof(Block) + current->size;
        current = current->next;
    }

    std::cout << std::endl;
}

void* MemoryManager::makeHandle(int n, size_t s) {
    void* masterPtr = firstFit(n * s);
    if (masterPtr == nullptr) {
        return nullptr;
    }
    masterPtrs.push_back(masterPtr);
    return &(masterPtrs.back());
};

void MemoryManager::freeHandle(Handle h) {
    // Iterate through the linked list of handles to find the one matching h
    for (auto it = masterPtrs.begin(); it != masterPtrs.end(); ++it) {
        if (*it == h) {
            // Remove the handle from the list and deallocate its memory
            masterPtrs.erase(it);
            deallocate(h);
            return;
        }
    }
    std::cerr << "Error: Handle not found" << std::endl;
}

void MemoryManager::lock(Handle h) {
    Block* current = (Block*) h;
    current->isLocked = true;
}

void MemoryManager::unlock(Handle h) {
    Block* current = (Block*) h;
    current->isLocked = false;
}

void MemoryManager::checkForLockedBlocks() {
    Block* current = head;
    while (current != nullptr) {
        if (current->isLocked) {
            std::cout << "Warning: locked block at address " << current << std::endl;
        }
        current = current->next;
    }
}

void MemoryManager::defrag() {
    // Lock all handles to ensure no blocks are moved during defragmentation
    for (void* ptr : masterPtrs) {
        Handle h = (Handle) ptr;
        lock(h);
    }

    // Merge adjacent free blocks
    Block* current = head;
    while (current != nullptr) {
        if (current->isFree && current->next != nullptr && current->next->isFree) {
            Block* next_block = current->next;
            current->size += sizeof(Block) + next_block->size;
            current->next = next_block->next;
        } else {
            current = current->next;
        }
    }

    // Unlock all handles
    for (void* ptr : masterPtrs) {
        Handle h = (Handle) ptr;
        unlock(h);
    }

    if (verbose) { printHeapMap(); }
}

Block* MemoryManager::findFreeBlock(size_t size) {
    Block* curr = nullptr;
    
    // Search in the appropriate list of common hole sizes
    if (size <= 128) {
        for (int i = 0; i < smallList.size(); i++) {
            if (smallList[i]->size >= size) {
                curr = smallList[i];
                break;
            }
        }
    } else if (size <= 256) {
        for (int i = 0; i < mediumList.size(); i++) {
            if (mediumList[i]->size >= size) {
                curr = mediumList[i];
                break;
            }
        }
    } else if (size <= 512) {
        for (int i = 0; i < largeList.size(); i++) {
            if (largeList[i]->size >= size) {
                curr = largeList[i];
                break;
            }
        }
    } else {
        for (int i = 0; i < veryLargeList.size(); i++) {
            if (veryLargeList[i]->size >= size) {
                curr = veryLargeList[i];
                break;
            }
        }
    }
    
    if (curr == nullptr) {
        // Resort to original hole fitting algorithm
        curr = head;
        Block* bestFit = nullptr;
        size_t minDiff = UINT_MAX;
        
        while (curr != nullptr) {
            if (curr->isFree && curr->size >= size) {
                size_t diff = curr->size - size;
                if (diff == 0) {
                    break;
                } else if (diff < minDiff) {
                    minDiff = diff;
                    bestFit = curr;
                }
            }
            curr = curr->next;
        }
        
        curr = bestFit;
    }
    
    return curr;
}

void* MemoryManager::smartFit(size_t size) {
    // Find a free block that is large enough to hold the requested size
    Block* block = findFreeBlock(size);
    if (!block) {
        return nullptr; // No free block large enough
    }

    // Split the block if it is larger than the requested size
    if (block->size > size + sizeof(Block)) {
        splitBlock(block, size);
    }

    // Mark the block as used
    block->isFree = false;

    // Return a pointer to the beginning of the block
    return (void*)(block + 1);
}

void MemoryManager::smartFree(void* ptr) {
    // Calculate the block pointer from the given pointer
    Block* block = (Block*)ptr - 1;

    // Mark the block as free
    block->isFree = true;

    // Merge adjacent free b();
}

void* MemoryManager::smartMakeHandle(int n, size_t s) {
    // Allocate memory for the handle
    void* handle = smartFit(sizeof(int*) + sizeof(Block*));
    if (!handle) {
        return nullptr; // Allocation failed
    }

    // Set the handle values
    int* id = (int*)handle;
    Block** blockPtr = (Block**)(id + 1);
    *id = n;
    *blockPtr = findFreeBlock(s);

    // Mark the block as used
    (*blockPtr)->isFree = false;

    // Return the handle pointer
    return handle;
}

void MemoryManager::splitBlock(Block* block, size_t size) {
    // Compute the size of the new block
    size_t blockSize = block->size - size - sizeof(Block);

    // Split the block
    Block* newBlock = (Block*)((char*)block + size + sizeof(Block));
    newBlock->isFree = true;
    newBlock->size = blockSize;
    newBlock->next = block->next;
    block->next = newBlock;
    block->size = size;
    block->isFree = false;

    // Add the new block to the appropriate free block list
    if (blockSize <= 128) {
        smallList.push_back(newBlock);
    } else if (blockSize <= 256) {
        mediumList.push_back(newBlock);
    } else if (blockSize <= 512) {
        largeList.push_back(newBlock);
    } else {
        veryLargeList.push_back(newBlock);
    }
}

// void MemoryManager::mergeBlocks() {
//     // Merge adjacent free blocks in each free block list
//     for (const auto& blockList : {smallList, mediumList, largeList, veryLargeList}) {
//         auto it = blockList.begin();
//         while (it != blockList.end()) {
//             auto curr = *it;
//             auto next = curr->next;
//             if (next != nullptr && next->isFree) {
//                 curr->next = next->next;
//                 curr->size += sizeof(Block) + next->size;
//                 next->size = 0;
//                 next->next = nullptr;
//                 it = blockList.erase(it);
//                 operator delete(next);
//             } else {
//                 ++it;
//             }
//         }
//     }

//     // Merge adjacent free blocks in the entire memory heap
//     Block* curr = head;
//     while (curr != nullptr) {
//         if (curr->isFree && curr->next != nullptr && curr->next->isFree) {
//             auto next = curr->next;
//             curr->next = next->next;
//             curr->size += sizeof(Block) + next->size;
//             next->size = 0;
//             next->next = nullptr;
//             operator delete(next);
//         }
//         curr = curr->next;
//     }
// }


// void MemoryManager::defrag() {
//     if (!head || !head->next) {
//         return; // nothing to defrag
//     }
//     Block* curr = head;
//     while (curr->next) {
//         if (curr->isFree && curr->next->isFree) {
//             // merge adjacent free blocks
//             curr->size += sizeof(Block) + curr->next->size;
//             curr->next = curr->next->next;
//         } else {
//             curr = curr->next;
//         }
//     }
//     mergeBlocks();
// }
