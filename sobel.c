
#include <CVIPtoolkit.h>
#include <CVIPimage.h>
#include <CVIPdef.h>
#include <CVIPgeometry.h>
#include "CVIPlab.h"
#include <CVIPconvert.h>
#include <CVIPview.h>
#define VIEWER "picture"
#define VIDEO_APP "SunVideo &"


Image* sobel_edge_lab(Image* inputImage) {
	byte** image; 	/* 2-d matrix data pointer */
	float** image_new;
	int s1, s2;

	unsigned int
		no_of_bands,	/* number of colorbands */
		no_of_rows,		/* number of rows */
		no_of_cols,		/* number of colomns */
		r,				/* row index */
		c, 				/* column index */
		bands;			/* band index */

	IMAGE_FORMAT format = getFileFormat_Image(inputImage);
	COLOR_FORMAT color = getColorSpace_Image(inputImage);
	CVIP_TYPE cvtype = getDataType_Image(inputImage);
	FORMAT dataformat = getDataFormat_Image(inputImage);

	no_of_bands = getNoOfBands_Image(inputImage);
	no_of_rows = getNoOfRows_Image(inputImage);
	no_of_cols = getNoOfCols_Image(inputImage);

	Image* output_image = new_Image(format, color, no_of_bands, no_of_rows, no_of_cols, CVIP_FLOAT, REAL);

	for (bands = 0; bands < no_of_bands; bands++) {
		image = getData_Image(inputImage, bands);
		image_new = getData_Image(output_image, bands);

		for (r = 1; r < (no_of_rows - 1); r++) {
			for (c = 1; c < (no_of_cols - 1); c++) {
				s1 = -1 * image[r - 1][c - 1];
				s1 += -2 * image[r - 1][c];
				s1 += -1 * image[r - 1][c + 1];
				s1 += 1 * image[r + 1][c - 1];
				s1 += 2 * image[r + 1][c];
				s1 += 1 * image[r + 1][c + 1];

				s2 = -1 * image[r - 1][c - 1];
				s2 += 1 * image[r - 1][c+1];
				s2 += -2 * image[r][c - 1];
				s2 += 2 * image[r][c + 1];
				s2 += -1 * image[r + 1][c-1];
				s2 += 1 * image[r + 1][c + 1];

				image_new[r][c] = sqrt((double)s1 * s1 + (double)s2 * s2);


			}
		}
	}
	output_image = remap_Image(output_image, CVIP_BYTE, 0, 255);
	return output_image;
}
/*
** end of function 
*/
