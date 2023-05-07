
#include <stdio.h>
#include "rasterImage.h"
#include "mallocChoice.h"

//---------------------------------------
//	Image utility functions.
//	Should be moved to some Image.c file
//---------------------------------------
RasterImage newImage(unsigned int width, unsigned int height, ImageType type)
{
	if (width<3 || height<3)
	{
		printf("Image size should be at least 3x3\n");
		exit(14);
	}

	RasterImage img;
	img.width = width;
	img.height = height;
	img.type = type;
	switch (type)
	{
		case RGBA32_RASTER:
		img.bytesPerPixel = 4;
		break;
		
		case GRAY_RASTER:
		img.bytesPerPixel = 1;
		break;
		
		case FLOAT_RASTER:
		img.bytesPerPixel = sizeof(float);
		break;
	}

	img.bytesPerRow = img.bytesPerPixel * width;

	unsigned int effectiveWidth = img.bytesPerRow / img.bytesPerPixel;	
	img.raster = (void*) calloc(height*effectiveWidth, img.bytesPerPixel);
	
	// 	If you implement the 2D raster, this is where you would "scaffold" the 2D array 
	//	on top of the 1D raster.
	img.raster2D = (void*) calloc(img.height, 2 * sizeof(int));

	int* ptr2D = (int*) img.raster2D;
	int rowByRow = 0;

	for (int i = 0; i < img.height; i++) {
		int* rowPtr1D = (int*) img.raster + rowByRow;
		ptr2D[i] = *rowPtr1D;
		rowByRow += img.width;
	}
	return img;
}
