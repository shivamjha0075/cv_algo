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
#define VIEWER "picture"
#define VIDEO_APP "SunVideo &"

Image* spatial_lowpass(Image* inputImage)
{
    byte** image;
    byte** image2;
    int x_coef = 0;
    int y_coef = 0;
    printf("Enter spatial filter mask coefficient (3x3 / 5x5) : \n");

    printf("Enter mask size: ");
    scanf("%d", &x_coef);
    y_coef = x_coef;
    int mask[5][5] = {
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1}
    };
    
    if (x_coef == 3 && y_coef == 3) {
        mask[0][0] = 0;
        mask[0][4] = 0;
        mask[4][0] = 0;
        mask[4][4] = 0;
    }

    int rows = getNoOfRows_Image(inputImage);
    int cols = getNoOfCols_Image(inputImage);
    unsigned no_of_bands;
    no_of_bands = getNoOfBands_Image(inputImage);
    IMAGE_FORMAT format = getFileFormat_Image(inputImage);
    COLOR_FORMAT color = getColorSpace_Image(inputImage);
    CVIP_TYPE cvtype = getDataType_Image(inputImage);
    FORMAT dataformat = getDataFormat_Image(inputImage);

    Image* outputImg = new_Image(getFileFormat_Image(inputImage), getColorSpace_Image(inputImage), no_of_bands ,rows, cols,cvtype, dataformat);


    for (int bands = 0; bands < no_of_bands; bands++) {

        image = getData_Image(inputImage, bands);
        image2 = getData_Image(outputImg, bands);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int sum = 0;
                int num_pixels = 0;
                for (int m = 0; m < x_coef; m++) {
                    for (int n = 0; n < y_coef; n++) {
                        int row_index = i + m - (x_coef / 2);
                        int col_index = j + n - (y_coef / 2);
                        
                        if (row_index >= 0 && row_index < rows && col_index >= 0 && col_index < cols) {
                            sum += image[row_index][col_index] * mask[m][n];
                            num_pixels++;
                        }

                    }
                }
                image2[i][j] = (byte)(sum / num_pixels);
            }
        }

    }
    return outputImg;
}

Image* spatial_highpass(Image* inputImage)
{
    byte** image;
    byte** image2;
    int x_coef = 0;
    int y_coef = 0;
    printf("Enter spatial filter mask coefficient (3x3 / 5x5) : \n");

    printf("Enter mask size: ");
    scanf("%d", &x_coef);
    y_coef = x_coef;
    int mask[5][5] = {
        {-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1},
        {-1,-1,25,-1,-1},
        {-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1},
    };

    if (x_coef == 3 && y_coef == 3) {
        mask[0][0] = 0;

        mask[0][2] =0 ;

        mask[0][4] = 0;

        mask[1][1] = 0;

        mask[1][2] = 0;

        mask[1][3] = 0;

        mask[2][0] = 0;

        mask[2][2] = 9;

        mask[2][3] = 0;

        mask[2][4] = 0;

        mask[3][1] = 0;

        mask[3][2] = 0;

        mask[3][3] = 0;

        mask[4][0] = 0;

        mask[4][2] = 0;

        mask[4][4] = 0;

    }

    int rows = getNoOfRows_Image(inputImage);
    int cols = getNoOfCols_Image(inputImage);
    unsigned no_of_bands;
    no_of_bands = getNoOfBands_Image(inputImage);
    IMAGE_FORMAT format = getFileFormat_Image(inputImage);
    COLOR_FORMAT color = getColorSpace_Image(inputImage);
    CVIP_TYPE cvtype = getDataType_Image(inputImage);
    FORMAT dataformat = getDataFormat_Image(inputImage);

    Image* outputImg = new_Image(getFileFormat_Image(inputImage), getColorSpace_Image(inputImage), no_of_bands, rows, cols, cvtype, dataformat);


    for (int bands = 0; bands < no_of_bands; bands++) {

        image = getData_Image(inputImage, bands);
        image2 = getData_Image(outputImg, bands);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int sum = 0;
                int num_pixels = 0;
                for (int m = 0; m < x_coef; m++) {
                    for (int n = 0; n < y_coef; n++) {
                        int row_index = i + m - (x_coef / 2);
                        int col_index = j + n - (y_coef / 2);

                        if (row_index >= 0 && row_index < rows && col_index >= 0 && col_index < cols) {
                            sum += image[row_index][col_index]* mask[m][n];
                            num_pixels++;
                        }

                    }
                }
                image2[i][j] = (byte)(sum / num_pixels);
            }
        }

    }
    return outputImg;
}