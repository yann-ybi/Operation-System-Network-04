
#include <stdlib.h>
#include <stdio.h>
#include "./applications.h"


/**	struct to parse command line argument paths 
 *	@param	tgaPath  string path to the tga file
 *	@param	dirPath  string path to the output directory 
 *	@param	rot      option for image rotation
 */
typedef struct {
    char* tgaPath;
    char* dirPath;
    char* rot;
} Parsed;

// this function parse the program arguments withing our Parsed structure
Parsed parseArgs(int argc, char** argv);

Parsed parseArgs(int argc, char** argv) {
    if (argc != 4) {
        printf("Incorrect number of arguments");
        exit(BAD_NUM_ARGS);
    }
    char* tgaPath = argv[2]; char* dirPath = argv[3];
    char* rot = argv[1];

    if (!isaTGAfile(tgaPath)) {
        printf("The argument is not a tga file: %s", tgaPath);
        exit(1);
    }
    if (!tgaPathIsValid(tgaPath)) {
        printf("File not found: %s", tgaPath);
        exit(1);
    }
    if (!dirIsValid(dirPath)) {
        printf("Dir not found: %s", dirPath);
        exit(1);
    }
    Parsed parsed = {tgaPath, dirPath, rot};
    return parsed;
}