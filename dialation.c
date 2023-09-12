#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPlab.h"
Image* dilation_lab(Image* inputImage, int struc[9]) {
	byte** image; /* 2-d matrix data pointer */
	byte** image_new;
	unsigned int
		r, /* row index */
		c, /* column index */
		bands; /* band index */
	unsigned int
		no_of_rows, /* number of rows in image */
		no_of_cols, /* number of columns in image */
		no_of_bands; /* number of image bands */
	/*
	** Gets the number of image bands (planes)
	*/
	no_of_bands = getNoOfBands_Image(inputImage);
	/*
	** Gets the number of rows in the input image
	*/
	no_of_rows = getNoOfRows_Image(inputImage);
	/*

	** Gets the number of columns in the input image
	*/
	no_of_cols = getNoOfCols_Image(inputImage);
	IMAGE_FORMAT format = getFileFormat_Image(inputImage);
	COLOR_FORMAT color = getColorSpace_Image(inputImage);
	CVIP_TYPE cvtype = getDataType_Image(inputImage);
	FORMAT dataformat = getDataFormat_Image(inputImage);
	no_of_bands = getNoOfBands_Image(inputImage);
	Image* outputImage = new_Image(format, color, no_of_bands, no_of_rows,
		no_of_rows, cvtype, dataformat);
	for (bands = 0; bands < no_of_bands; bands++) {
		/*
		** reference each band of image data in 2-d matrix form;
		** which is used for reading and writing the pixel values
		*/
		image = getData_Image(inputImage, bands);
		image_new = getData_Image(outputImage, bands);
		//Copy input image to output image
		for (r = 0; r < no_of_rows; r++) {
			for (c = 0; c < no_of_cols; c++) {
				image_new[r][c] = image[r][c];
			}
		}
		//perform dilation pixel by pixel
		for (r = 1; r < (no_of_rows - 1); r++) {
			for (c = 1; c < (no_of_cols - 1); c++) {
				if (image[r][c] == 255) {
					image_new[r - 1][c - 1] = (image_new[r - 1][c - 1] ||
						struc[0]) * 255;
					image_new[r - 1][c] = (image_new[r - 1][c] ||
						struc[1]) * 255;
					image_new[r - 1][c + 1] = (image_new[r - 1][c + 1] ||
						struc[2]) * 255;
					image_new[r][c - 1] = (image_new[r][c - 1] ||
						struc[3]) * 255;
					image_new[r][c] = (image_new[r][c] ||
						struc[4]) * 255;
					image_new[r][c + 1] = (image_new[r][c + 1] ||
						struc[5]) * 255;
					image_new[r + 1][c - 1] = (image_new[r + 1][c - 1] ||
						struc[6]) * 255;
					image_new[r + 1][c] = (image_new[r + 1][c] ||
						struc[7]) * 255;
					image_new[r + 1][c + 1] = (image_new[r + 1][c + 1] ||
						struc[8]) * 255;
				}
			}
		}
	}
	return outputImage;
}
