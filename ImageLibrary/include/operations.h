
#include "rasterImage.h"



/**	Gets dimensions of a .tga image based on option modifiers.
 *	@param	image	    RasterImage struct of the image.
 *	@param  isWidth		option modifier to get the width of the image or not.
 *	@param  isHeight	option modifier to get the height of the image or not.
 *	@param  isVerbrose	option modifier to get a verbrose dimensions.
 *	@return a string with the dimensions of the RasterImage struct.
 */
char* getDimensions(RasterImage* image, bool isWidth, bool isHeight, bool isVerbrose); //change //change

/**	Removes all colors from a RasterImage image except the one from the color argument.
 *	@param	image	   pointer to a RasterImage struct.
 *	@param  colorIdx   Raster Image pixel color index.
 *	rgba[0] -> red, rgba[1] -> green, rgba[2] -> blue, rgba[3] -> alpha.
 */
void getColorFromImage(RasterImage* image, int colorIdx);

/**	Removesall colors from a RasterImage image except the color Red.
 *	@param	image	  RasterImage struct of the image.
 */
RasterImage getRFromImage(RasterImage image);

/**	Removes all colors from a RasterImage image except the Color Green.
 *	@param	image	  RasterImage struct of the image.
 */
RasterImage getGFromImage(RasterImage image);

/**	Removes all colors from a RasterImage image except the Color Blue.
 *	@param	image	  RasterImage struct of the image.
 */
RasterImage getBFromImage(RasterImage image);

/**	Cops a RasterImage image based on copping arguments: x, y, width, height.
 *	@param	image   pointer to RasterImage struct.
 *	@param	x	    x coordinate of the upper left rectangle of the crop.
 *	@param	y	    y coordinate of the upper left rectangle of the crop.
 *	@param	width   width of the crop rectangle.
 *	@param	height  height oof the crop rectangle.
 */
RasterImage cropImage(RasterImage* image, unsigned int x, unsigned int y, unsigned int width, unsigned int height); // change

/**	Does a left rotation of a RasterImage image by 90 degree.
 *	@param	image  pointer to RasterImage struct of the image.
 */
RasterImage rotateL90(RasterImage* image);

/**	Does a right rotation of a RasterImage image by 90 degree.
 *	@param	image    pointer to RasterImage struct of the image.
 */
RasterImage rotateR90(RasterImage* image);
