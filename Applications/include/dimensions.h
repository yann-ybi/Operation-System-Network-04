#include <stdlib.h>
#include <stdio.h>
#include "./applications.h"


/**	struct to parse command line argument option modier and path 
 *	@param  isOption option modifer
 *	@param	fpath    string path to the tga file
 */
typedef struct {
    bool isOption;
    char* fpath;
}Parsed;

/**	struct to parse an option from the command line argument 
 *	@param  isWidth		option modifier for the width
 *	@param  isHeight	option modifier for the height
 *	@param  isVerbrose	option modifier for verbrose
*	@param  error	    option modifier for error code
 */
typedef struct {
    bool isWidth;
    bool isHeight;
    bool isVerbrose;
    OpErrorCode error;
} Option;

// this function creates an Option object containing on booleans
Option newOp(bool isWidth, bool isHeight, bool isVerbrose);

// this function parse the option arguments given to the program inside of an Option structure then returns it
Option parseOptionInput(char* op);

// this function print the appropriate error message based on the enum error code using the option string
void printOpError(char* opString, OpErrorCode* error);

// this function parse the program arguments withing our Parsed structure
Parsed parseArgs(int argc, char** argv);


Option newOp(bool isWidth, bool isHeight, bool isVerbrose) {
    Option option;
    option.isWidth = isWidth;
    option.isHeight = isHeight;
    option.isVerbrose = isVerbrose;
    option.error = NO_OP_ERROR;
    return option;
}

Option parseOptionInput(char* op) {
    Option option = newOp(false, false, false);
    if (op[0] != '-') {
        printf("Invalid modifier: %c", op[0]);
        exit(UNKNOWN_OP);
    }
    op++;
    while (*op != '\0') {
        switch (*op) {
            case 'h':
                if (!option.isHeight) { option.isHeight = true; }
                else {
                    option.error = EXTRA_OP_H;
                }
                if (option.isWidth) { option.error = EXCLUSIVE_OPS; }
                break;
            case 'w':
                if (!option.isWidth) { option.isWidth = true; }
                else {
                    option.error = EXTRA_OP_W;
                }
                if (option.isHeight) { option.error = EXCLUSIVE_OPS; }
                break;
            case 'v':
                if (!option.isVerbrose) { option.isVerbrose = true; }
                else {
                    option.error = EXTRA_OP_V;
                }
                break;
            default:
                option.error = UNKNOWN_OP;
                break;
        }
        op++;
    }
    return option;
}

void printOpError(char* opString, OpErrorCode* error) {//out 
    switch (*error)
    {
    case UNKNOWN_OP:
        printf("Invalid modifier: %c", opString[1]);
        break;
    case EXTRA_OP_H:
        printf("The option modifier height -h should be used only once.");
        break;
    case EXTRA_OP_W:
        printf("The option modifier width -w should be used only once.");
        break;
    case EXTRA_OP_V:
        printf("The option modifier verbrose -v should be used only once.");
        break;
    case EXCLUSIVE_OPS:
        printf("Modifiers -w and -h cannot be used together.");
        break;
    default:
        break;
    }
}

Parsed parseArgs(int argc, char** argv) {
    if (argc != 2 && argc != 3) {
        printf("Invalid number of arguments: Multiple modifier chains not allowed.");
        exit(BAD_NUM_ARGS);
    }
    char* fpath;
    bool isOption = false;

    if (argc == 2) {
        fpath = argv[1];
        if (!isaTGAfile(argv[1])){
            printf("The argument is not a tga file: %s", argv[1]);
            exit(BAD_FILE_TYPE);
        }
        if (!tgaPathIsValid(fpath)) {
            printf("File cannot be read: %s", fpath);
            exit(BAD_FILE_PATH);
        }
    }
    else if (argc == 3) {
        fpath = argv[2];
        isOption = true;

        if (!isaTGAfile(argv[2])){
            printf("The argument is not a tga file: %s", argv[2]);
            exit(BAD_FILE_TYPE);
        }
        if (!tgaPathIsValid(fpath)) {
            printf("File cannot be read %s", fpath);
            exit(BAD_FILE_PATH);
        }
    }
    else {
        exit(BAD_FILE_TYPE);
    }
    Parsed parsed = { isOption, fpath };
    return parsed;
}