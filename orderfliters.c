#include <CVIPtoolkit.h>
#include <CVIPimage.h>
#include <CVIPdef.h>
#include <CVIPgeometry.h>
#include "CVIPlab.h"
#include <CVIPconvert.h>
#include <CVIPview.h>
#include "CVIParithlogic.h"
#include <math.h>
#include <stdio.h>
#include "CVIPdrawimg.h"
#include "CVIPtransform.h"



Image* meanfilter(Image* inputImage)
{
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

    byte** image_new;

    no_of_bands = getNoOfBands_Image(inputImage);
    no_of_rows = getNoOfRows_Image(inputImage);
    no_of_cols = getNoOfCols_Image(inputImage);

    Image* output_image = new_Image(format, color, no_of_bands, no_of_rows, no_of_cols, CVIP_BYTE, REAL);

    int kernal_size = 3;


    for (int bands = 0; bands < no_of_bands; bands++) {
        image = getData_Image(inputImage, bands);
        image_new = getData_Image(output_image, bands);
        for (r = 1; r < (no_of_rows - 1); r++) {
            for (c = 1; c < (no_of_cols - 1); c++) {
                int sum = 0;
                for (int i = -kernal_size / 2; i <= kernal_size / 2; i++) {
                    for (int j = -kernal_size / 2; j <= kernal_size / 2; j++) {
                        // Get the pixel value at (r+i, c+j) with boundary check
                        int x = r + i;
                        int y = c + j;
                        if (x < 0) x = 0;
                        if (x >= no_of_rows) x = no_of_rows - 1;
                        if (y < 0) y = 0;
                        if (y >= no_of_cols) y = no_of_cols - 1;
                        byte value = getData_Image(inputImage, x, y, bands);

                        // Add the pixel value to the sum
                        sum += value;
                    }
                    byte mean = sum / (kernal_size * kernal_size);
                    setPixel_Image(output_image,BYTE, r, c, bands, mean);
                }
            }
        }

    }
    return output_image;
}
