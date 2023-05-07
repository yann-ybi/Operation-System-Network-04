#include "replacementManager.h"
#include "replacementMalloc.h"
#include "heapSize.h"



MemoryManager manager(HEAPSIZE);

void* myMalloc(size_t size) {
    #if	FIT_CHOICE == FIRST_FIT
        return manager.firstFit(size);

    #elif FIT_CHOICE == BEST_FIT
        return manager.bestFit(size);

    #elif FIT_CHOICE == WORST_FIT
        return manager.worstFit(size);

    #else
        #error invalid fit choice

    #endif

}

void* myCalloc(size_t n, size_t s) {
    size_t size = n * s;

    #if	FIT_CHOICE == FIRST_FIT
        void* ptr = manager.firstFit(size);
        if (ptr != nullptr) {
            memset(ptr, 0, size);
        }
        return ptr;

    #elif FIT_CHOICE == BEST_FIT
        void* ptr = manager.bestFit(size);
        if (ptr != nullptr) {
            memset(ptr, 0, size);
        }
        return ptr;

    #elif FIT_CHOICE == WORST_FIT
        void* ptr = manager.worstFit(size);
        if (ptr != nullptr) {
            memset(ptr, 0, size);
        }
        return ptr;

    #else
        #error invalid fit choice
    #endif
};

void myFree(void* ptr) {
    manager.deallocate(ptr);
}

void verbose(bool v) {
    manager.verbose = v;
}

Handle makeHandle(int n, size_t s){
    return manager.makeHandle(n, s);
}

void freeHandle(Handle h) {
    return manager.freeHandle(h);
}

void myDefrag() {
    manager.defrag();
}

void* smartFit(size_t size) {
    return manager.smartFit(size);
}

void smartFree(void* ptr) {
    manager.smartFree(ptr);
}

void* smartMakeHandle(int n, size_t size) {
    return manager.smartMakeHandle(n, size);
}