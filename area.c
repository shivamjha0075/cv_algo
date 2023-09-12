
#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPlab.h"


#define 	WHITE_LAB	255
#define		BLACK_LAB	0



void* area_lab(Image* inputImage, unsigned int* center_row, unsigned int* center_col) {
	byte** image; /* 2-d matrix data pointer */
	unsigned int
		no_of_bands, /* number of colorbands */
		no_of_rows, /* number of rows */
		no_of_cols, /* number of colomns */
		r, /* row index */
		c, /* column index */
		r_c, /* center column */
		c_c, /* center row */
		bands, /* band index */
		row_counter,
		col_counter;
	float area;
	/*get number of rows, columns and colorbands */
	no_of_rows = getNoOfRows_Image(inputImage);
	no_of_cols = getNoOfCols_Image(inputImage);
	image = getData_Image(inputImage, 0);
	area = 0;
	for (r = 0; r < no_of_rows; r++) {
		for (c = 0; c < no_of_cols; c++) {
			area += image[r][c] / 255;
		}
	}
	r_c = 0;
	for (r = 0; r < no_of_rows; r++) {
		row_counter = 0;
		for (c = 0; c < no_of_cols; c++) {
			row_counter += image[r][c] / 255;
		}
		r_c += r * row_counter;
	}
	r_c = (unsigned int)r_c / area;
	c_c = 0;
	for (c = 0; c < no_of_cols; c++) {
		col_counter = 0;
		for (r = 0; r < no_of_rows; r++) {
			col_counter += (image[r][c] / 255);
		}
		c_c += c * col_counter;
	}
	c_c = (unsigned int)c_c / area;
	*center_row = r_c;
	*center_col = c_c;
	return;
}

