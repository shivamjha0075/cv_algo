/***************************************************************************
* =========================================================================
*
*   Shivam Jha
*
* =========================================================================
*
*             File Name: zoom_lab.c
*           Description: it contains the function to zoom BYTE images
*   Initial Coding Date: September 07, 2022
*           Portability: Standard (ANSI) C
*
*
****************************************************************************/

/*
** include header files
*/

#include <CVIPtoolkit.h>
#include <CVIPimage.h>
#include <CVIPdef.h>
#include <CVIPgeometry.h>
#include "CVIPlab.h"
#include <CVIPconvert.h>
#include <CVIPview.h>
#define VIEWER "picture"
#define VIDEO_APP "SunVideo &"

/*
**
*/

Image* zoom_lab(Image* inputImage, unsigned int x_coordinate, unsigned int y_coordinate, unsigned int height, unsigned int width, unsigned zoom_factor) {
	byte** image; 	/* 2-d matrix data pointer */
	byte** image_new;

	unsigned int
		no_of_bands,	/* number of colorbands */
		no_of_rows,		/* number of rows */
		no_of_cols,		/* number of colomns */
		r,				/* row index */
		c, 				/* column index */
		bands,			/* band index */
		r_offset,		/* row offset index */
		c_offset;		/* column offset index */


	IMAGE_FORMAT format = getFileFormat_Image(inputImage);
	COLOR_FORMAT color = getColorSpace_Image(inputImage);
	CVIP_TYPE cvtype = getDataType_Image(inputImage);
	FORMAT dataformat = getDataFormat_Image(inputImage);

	no_of_bands = getNoOfBands_Image(inputImage);

	/* calculate new image dimensions */
	no_of_rows = height * zoom_factor;
	no_of_cols = width * zoom_factor;

	Image *zoomed_image = new_Image(format, color, no_of_bands, no_of_rows, no_of_cols, cvtype, dataformat);


	/*
	** writes values 
	*/
	for (bands = 0; bands < no_of_bands; bands++) {

		
		image = getData_Image(inputImage, bands);
		image_new = getData_Image(zoomed_image, bands);
		for (r = 0; r < height; r++) {
			for (c = 0; c < width; c++) {
				for (c_offset = 0; c_offset < zoom_factor; c_offset++) {
					for (r_offset = 0; r_offset < zoom_factor; r_offset++) {
						image_new[r * zoom_factor + r_offset][c * zoom_factor + c_offset] = image[x_coordinate + r][y_coordinate + c];
					}
				}
			}
		}
	}

	return zoomed_image;
}
/*
** end of function zoom_lab
*/
