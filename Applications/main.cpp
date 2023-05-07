#include <iostream>
#include <vector>
#include "mallocChoice.h"

using namespace std;

using IntHandle = int**;

// g++ -Wall -std=c++20 -I MemoryManager/include -I Applications MemoryManager/src/*.cpp Applications/main.cpp -o prog
int main(int argc, char* argv[]) {

    int i = 1; size_t nbytes; void* baddy;
    std::vector<void*> addrs;
    int blockIdx;

    bool v = false;
    IntHandle handle;
    std::vector<IntHandle> handles;

    if (argc == 1) { exit(1); }

    if (strcmp(argv[1], "-v") == 0) {
        std::cout << "Verbose activated\n" << std::endl;
        v = true;
        i += 1;
    }
    else { std::cout << "No verbose\n" << std::endl; }
    verbose(v);

    for (;i < argc; i += 2) {

        switch (*argv[i])
        {
        case 'm':
            nbytes = static_cast<size_t>(stoi(argv[i+1]));
            std::cout << "Allocate a block of " << nbytes << " bytes with my malloc." << std::endl;
            baddy = malloc(nbytes);
            addrs.push_back(baddy);
            
            ((char*)baddy)[0] = 'a';
            break;

        case 'c':
            nbytes = static_cast<size_t>(stoi(argv[i+1]));
            std::cout << "Allocate a block of " << nbytes << " bytes with my calloc" << std::endl;
            baddy = calloc(0, nbytes);
            addrs.push_back(baddy);
            break;

        case 'f':
            blockIdx = std::stoi(argv[i+1]);
            baddy = addrs[blockIdx];
            std::cout << "Free a block at address " << baddy << " at index " << blockIdx << std::endl;
            free(baddy);
            break;


        case 'H':
            nbytes = static_cast<size_t>(stoi(argv[i+1]));
            std::cout << "Make a hand for a block of " << nbytes * sizeof(int) << " bytes with my makeHande." << std::endl; 
            handle = (IntHandle) makeHandle(nbytes, sizeof(int)); 
            handles.push_back(handle);
            break;

        case 'F':
            std::cout << "Free handle block of " << nbytes * sizeof(int) << " bytes with my makeHande." << std::endl; 
            freeHandle(handles[stoi(argv[i+1])]); 
            // handles.erase(handles.begin() + stoi(argv[i+1]));
            break;

        case 'd':
            std::cout << "Defragment heap." << std::endl;
            std::cout << std::endl;
            myDefrag();
            i += 1;
            break;

        case 's':
            nbytes = static_cast<size_t>(stoi(argv[i+1]));
            std::cout << "smart Fit a block of " << nbytes << " bytes with my malloc." << std::endl;
            baddy = smartFit(nbytes);
            addrs.push_back(baddy);
            break;

        case 'x':
            blockIdx = std::stoi(argv[i+1]);
            baddy = addrs[blockIdx];
            std::cout << "Smart Free a block at address " << baddy << " at index " << blockIdx << std::endl;
            smartFree(baddy);
            break;

        default:
            std::cerr << "Invalid argument(s) " << std::endl;
            break;
        }      
    }
    
}

