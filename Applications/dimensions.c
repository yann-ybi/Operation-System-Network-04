// This program named dimensions takes as argument the path to a TGA image file and reports the dimensions of the image. This program may be called with different optional modifiers that affect the output of the program:
// • -h Output image height only; • -w Output image width only; • -v verbose output.
// The modifier -v may be combined with -h or with -w, in either order, but the modifiers -h and -w are mutually exclusive.

// g++ -Wall -std=c++20 -I MemoryManager/include -I Applications -I Applications/include -I ImageLibrary/include MemoryManager/src/*.cpp ImageLibrary/src/* Applications/dimensions.c -o dim
// ./dim Images/Tyler.tga

#include <dirent.h>
#include "dimensions.h"
#include "mallocChoice.h"

int main(int argc, char** argv) {

    Parsed parsed = parseArgs(argc, argv);

    if (!parsed.isOption) {
        Option option = newOp(false, false, false);
        RasterImage image = readTGA(parsed.fpath);

        char* output = getDimensions(&image, option.isWidth, option.isHeight, option.isVerbrose);
        printf("%s\n", output);

        free(output);
    }
    else {
        char* opString = argv[1];

        Option option = parseOptionInput(opString);

        printOpError(opString, &option.error);

        if (option.error != NO_OP_ERROR) { exit(option.error); }
        else {
            RasterImage image = readTGA(parsed.fpath);

            char* output = getDimensions(&image, option.isWidth, option.isHeight, option.isVerbrose);
            printf("%s\n", output);
            
            free(output);
        }
    }
    return 0;
}
