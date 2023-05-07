// Yann Youbi
// This header contains functions and structures used by our applications programs

#include "stdbool.h"


#include <cstring>

#include "imageIO_TGA.h"
#include "operations.h"

// this function takes a string path to a file, returns true is the path is valid and false if the path is not
bool tgaPathIsValid(char* fpath);
// this function takes a string path to a direct, returns true is the path is valid and false if the path is not
bool dirIsValid(char* dirPath);
// this function takes a string path, and return just the name of the file with no extentions
char* getFileName(char* imgPath);

// returns true if the file is a tga file, false otherwise
bool isaTGAfile(char* arg);

enum ErrorCode {
    BAD_NUM_ARGS = 1,
    BAD_FILE_PATH,
    BAD_FILE_TYPE,
    UNKNOWN_ARGUM,
    TOO_LONG_ARG,
};

typedef enum {
    NO_OP_ERROR = 6,
    UNKNOWN_OP,
    EXTRA_OP_H,
    EXTRA_OP_W,
    EXTRA_OP_V,
    EXCLUSIVE_OPS,
} OpErrorCode;


bool tgaPathIsValid(char* fpath) {
    FILE* tga_in = fopen(fpath, "rb" );
    if (tga_in == NULL) { return false; } else { return true; }
}

bool dirIsValid(char* dirPath) {
    DIR* dir = opendir(dirPath);
    if (dir == NULL) { return false; } else { return true; }
}
char* getFileName(char* imgPath) {
    return strtok(strrchr(imgPath, '/'), ".");
}
bool isaTGAfile(char* arg) {
    char* str = arg + (strlen(arg) - 4);
    char ext[5] = ".tga";

    if (strcmp(ext, str) == 0) {
        return true;
    } 
    else { return false; }
}