
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "rasterImage.h"
#include "operations.h"
#include "mallocChoice.h"

char* getDimensions(RasterImage* image, bool isWidth, bool isHeight, bool isVerbrose) {
    if (isHeight && !isVerbrose) {
        char* strh = (char*) malloc(6);
        sprintf(strh, "%d", image->height);
        return strh;
    }
    else if (isWidth && !isVerbrose) {
        char* strw = (char*) malloc(6);
        sprintf(strw, "%d", image->width);
        return strw;
    }
    else if (isVerbrose) {
        if (isHeight && !isWidth) {
            char* hOut = (char*) malloc(20);
            sprintf(hOut, "height: %d", image->height);
            return hOut;
        }
        else if (!isHeight && isWidth) {
            char* wOut = (char*) malloc(20);
            sprintf(wOut, "width: %d", image->width);
            return wOut;
        }
        else {
            char* whOut = (char*) malloc(20);
            sprintf(whOut, "width: %d, height: %d", image->width, image->height);
            return whOut;
        }
    }
    else {
        char* whOut = (char*) malloc(12);
        sprintf(whOut, "%d %d", image->width, image->height);
        return whOut;
    }
}


void getColorFromImage(RasterImage* image, int colorIdx) {
    
    int* raster = (int*) (image->raster);

    for (unsigned int i = 0; i < image->height; i++)
    {
        for (unsigned int j = 0; j < image->width; j++)
        {
            unsigned char* rgba = (unsigned char*) (raster + i * image->width + j);
            //	rgba[0] -> red, rgba[1] -> green, rgba[2] -> blue, rgba[3] -> alpha
            for (int k = 0; k < 4; k ++) { if (k != colorIdx) { rgba[k] = 0x00; } }

        }
    }
}

RasterImage getRFromImage(RasterImage image) {
    getColorFromImage(&image, 0);
    return image;
}

RasterImage getGFromImage(RasterImage image) {
    getColorFromImage(&image, 1);
    return image;
}

RasterImage getBFromImage(RasterImage image) {
    getColorFromImage(&image, 2);
    return image;
}

RasterImage cropImage(RasterImage* image, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    RasterImage cropImage = newImage(width, height, image->type);

    unsigned int highestCropY = y + height;
    unsigned int highestCropX = x + width;

    int currIdx = 0;
    int* rowPtr = (int*) cropImage.raster;
    for (unsigned int colIdx = x; colIdx < highestCropX; colIdx++) 
    {
        for (unsigned int rowIdx = y; rowIdx < highestCropY; rowIdx++)
        {
            rowPtr[currIdx++] = *((int*) image->raster + (colIdx * image->width + rowIdx));
        }
    }
    return cropImage;
}

RasterImage rotateL90(RasterImage* image) {
    RasterImage rotImg = newImage(image->height, image->width, image->type);

    unsigned int idx = 0;
    int* ptr = (int*) rotImg.raster;
    for (unsigned int x = 0; x < image->width; x++)
    {
        for (unsigned int y = 0; y < image->height; y++)
        {
            ptr[idx] = *((int*) image->raster + (y * image->width + (image->width - x)));
            idx++;
        }
    }
    return rotImg;
}

RasterImage rotateR90(RasterImage* image) {
    RasterImage rotImg = newImage(image->height, image->width, image->type);

    unsigned int idx = 0;
    int* ptr = (int*) rotImg.raster;
    for (unsigned int x = 0; x < image->width; x++)
    {
        for (unsigned int y = 0; y < image->height; y++)
        {
            ptr[idx] = *((int*) image->raster + ((image->height - y) * image->width + x));
            idx++;
        }
    }
    return rotImg;
}
