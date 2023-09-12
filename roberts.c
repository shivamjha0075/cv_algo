
#include <CVIPtoolkit.h>
#include <CVIPimage.h>
#include <CVIPdef.h>
#include <CVIPgeometry.h>
#include "CVIPlab.h"
#include <CVIPconvert.h>
#include <CVIPview.h>
#define VIEWER "picture"
#define VIDEO_APP "SunVideo &"


Image* roberts_edge_lab(Image* inputImage, int absolute ) {
	byte** image; 	/* 2-d matrix data pointer */

	unsigned int
		no_of_bands,	/* number of colorbands */
		no_of_rows,		/* number of rows */
		no_of_cols,		/* number of colomns */
		r,				/* row index */
		c, 				/* column index */
		bands;		/* band index */

	double v1, v2;

	IMAGE_FORMAT format = getFileFormat_Image(inputImage);
	COLOR_FORMAT color = getColorSpace_Image(inputImage);
	CVIP_TYPE cvtype = getDataType_Image(inputImage);
	FORMAT dataformat = getDataFormat_Image(inputImage);

	float** image_new;

	no_of_bands = getNoOfBands_Image(inputImage);
	no_of_rows = getNoOfRows_Image(inputImage);
	no_of_cols = getNoOfCols_Image(inputImage);

	Image* output_image = new_Image(format, color, no_of_bands, no_of_rows, no_of_cols, CVIP_FLOAT, REAL);

	for (bands = 0; bands < no_of_bands; bands++) {

		image = getData_Image(inputImage, bands);
		image_new = getData_Image(output_image, bands);

		for (r = 1; r < (no_of_rows - 1); r++) {
			for (c = 1; c < (no_of_cols - 1); c++) {
				if (!absolute) {
					v1 = image[r][c] - image[r - 1][c - 1];
					v2 = image[r][c - 1] - image[r - 1][c];
					image_new[r][c] = sqrt(v1 * v1 + v2 * v2);
				}
				else {
					v1 = abs((image[r][c] - image[r - 1][c - 1]));
					v2 = abs((image[r][c - 1] - image[r - 1][c]));
					image_new[r][c] = v1 + v2;
				}

			}
		}
	}
	output_image = remap_Image(output_image, CVIP_BYTE, 0, 255);
	return output_image;
}
/*
** end of function 
*/
