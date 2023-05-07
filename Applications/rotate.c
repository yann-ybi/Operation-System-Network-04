// The program takes as arguments a string specifying the rotation to perform, the path to a valid TGA image file, and the path to an output directory. It writes in the output directory a new image file that contains the rotated image.
// The string specifying the rotation can be one of the following: l (rotate left by 90 degree), r (rotate right by 90 degree), ll or rr (rotate by 180 degree).
// The name of the output image should be that of the input image, with a suffix indicating the rotation applied. For example, if the input image is named myImage.tga, and an “ll” roatation wasapplied,thentheoutputimageshouldbemyImage [ll].tga.


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <stdbool.h>
#include <dirent.h>


#include "imageIO_TGA.h"
#include "operations.h"


// g++ -Wall -std=c++20 -I MemoryManager/include -I Applications -I Applications/include -I ImageLibrary/include MemoryManager/src/*.cpp ImageLibrary/src/* Applications/rotate.c -o rot
//./rot l Images/Tyler.tga Outputs
//./rot r Images/Tyler.tga Outputs
//./rot ll Images/Tyler.tga Outputs

#include "rotate.h"

#include "mallocChoice.h"

int main(int argc, char** argv) {

    Parsed parsed = parseArgs(argc, argv);

    RasterImage image = readTGA(parsed.tgaPath);
    RasterImage rotImg;

    unsigned int lCount = 0;
    unsigned int rCount = 0;

    while ((*(parsed.rot)) != '\0') {
        switch (*(parsed.rot))
        {
        case 'l':
            lCount++;
            break;

        case 'r':
            rCount++;
            break;
        case 'L':
            lCount++;
            break;

        case 'R':
            rCount++;
            break;

        default:
            printf("Invalid rotation string: %s", argv[1]);
            exit(UNKNOWN_ARGUM);
            break;
        }
        parsed.rot++;
    }

    int rFinal = rCount - lCount;
    int lFinal = lCount - rCount;

    if(rFinal < 0) { rFinal = 0; }
    if(lFinal < 0) { lFinal = 0; }

    while (rFinal % 3 == 0 && rFinal != 0) {
        rFinal -= 3;
        lFinal++;
    }
    while (lFinal % 3 == 0 && lFinal != 0) {
        rFinal -= 3;
        lFinal++;
    }
    
    if (rFinal > 0 || lFinal > 0){
        if (rFinal > 0) {
            while (rFinal % 4 == 0) {
                rFinal /= 4;
            }
            char* rFinalStr = (char*) calloc(rFinal + 1, sizeof(char));
            for (int i = 0; i < rFinal; i++) {
                rFinalStr[i] = 'r';
                rotImg = rotateR90(&image);
                image = rotImg;
            }
            char* fname = getFileName(parsed.tgaPath);
            char* rotPath = (char*) calloc(strlen(parsed.dirPath) + strlen(fname) + 4, 1);
            sprintf(rotPath, "%s%s [%s].tga", parsed.dirPath, fname, rFinalStr);
            writeTGA(rotPath, &image);

            free(rotPath);
            free(rFinalStr);
        }
        else if (lFinal > 0) { 
            while (lFinal % 4 == 0) {
                lFinal /= 4;
            }
            char* lFinalStr = (char*) calloc(lFinal + 1, sizeof(char));
            for (int i = 0; i < lFinal; i++) {
                lFinalStr[i] = 'l';
                rotImg = rotateL90(&image);
                image = rotImg;
            }
            char* fname = getFileName(parsed.tgaPath);
            char* rotPath = (char*) calloc(strlen(parsed.dirPath) + strlen(fname) + 4, 1);
            sprintf(rotPath, "%s%s [%s].tga", parsed.dirPath, fname, lFinalStr);
            writeTGA(rotPath, &image);

            free(rotPath);
            free(lFinalStr);
        }

    }
    else {
        char* fname = getFileName(parsed.tgaPath);
        char* rotPath = (char*) calloc(strlen(parsed.dirPath) + strlen(fname) + 4, 1);
        sprintf(rotPath, "%s%s [].tga", parsed.dirPath, fname);
        writeTGA(rotPath, &image);
        
        free(fname);
        free(rotPath);
    }
    return 0;
}