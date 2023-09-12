#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPlab.h"
/*
**
*/
void* euler_lab(Image* inputImage, int* conv, int
	* conc) {
	byte** image; /* 2-d matrix data pointer */
	unsigned int
		no_of_bands, /* number of colorbands */
		no_of_rows, /* number of rows */
		no_of_cols, /* number of colomns */
		r, /* row index */
		c; /* column index */
	/*get number of rows, columns and colorbands */
	no_of_rows = getNoOfRows_Image(inputImage);
	no_of_cols = getNoOfCols_Image(inputImage);
	image = getData_Image(inputImage, 0);
	*conc = 0;
	*conv = 0;
		for (r = 0; r < (no_of_rows - 1); r++) {
			for (c = 0; c < (no_of_cols - 1); c++) {
				if (image[r][c] == 0) {
					if (image[r + 1][c] == 0) {
						if (image[r][c + 1] == 0) {
							if (image[r + 1][c + 1] == 255) {
								(*conv)++;
							}
						}
					}
				}
				if (image[r][c] == 0) {
					if (image[r + 1][c] == 255) {
						if (image[r][c + 1] == 255) {
							if (image[r + 1][c + 1] == 255) {
								(*conc)++;
							}
						}
					}
				}
			}
		}
	return;
}
