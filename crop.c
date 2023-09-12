#include <CVIPtoolkit.h>
#include <CVIPimage.h>
#include <CVIPdef.h>
#include <CVIPgeometry.h>
#include "CVIPlab.h"
#include <CVIPconvert.h>
#include <CVIPview.h>
#define VIEWER "picture"
#define VIDEO_APP "SunVideo &"

Image* croplab(Image *inputImage, unsigned int x, unsigned int y, unsigned row_offset, unsigned col_offset)
{
	byte** new_image;
	byte** image;
	unsigned int 		r,		/* row index */
		c, 		/* column index */
		bands;		/* band index */

	unsigned int no_of_bands;	/* number of image bands */	
	IMAGE_FORMAT format = getFileFormat_Image(inputImage);
	COLOR_FORMAT color = getColorSpace_Image(inputImage);
	CVIP_TYPE cviptype = getDataType_Image(inputImage);
	FORMAT dataformat = getDataFormat_Image(inputImage);
	no_of_bands = getNoOfBands_Image(inputImage);
	Image* croppedImage = new_Image(format, color, no_of_bands, row_offset, col_offset, cviptype, dataformat);

		for (bands = 0; bands < no_of_bands; bands++) {
			/*
			** reference each band of image data in 2-d matrix form;
			** which is used for reading and writing the pixel values
			*/
			image = getData_Image(inputImage, bands);
			new_image = getData_Image(croppedImage, bands);
			for (r = 0; r < row_offset - 1; r++) {
				for (c = 0; c < col_offset - 1; c++) {
					new_image[r][c] = image[x + r][y + c];
				}
			}
		}

	return croppedImage;

}
