#include <CVIPtoolkit.h>
#include <CVIPimage.h>
#include <CVIPdef.h>
#include <CVIPgeometry.h>
#include "CVIPlab.h"
#include <CVIPconvert.h>
#include <CVIPview.h>
#include <math.h>
#include <stdio.h>
#define VIEWER "picture"
#define VIDEO_APP "SunVideo &"

float rmserror(Image* inputImage, Image* inputImage2)
{
    byte** image;
    byte** image2;
    unsigned int bands; 
    
    int rows = getNoOfRows_Image(inputImage);
    int cols = getNoOfCols_Image(inputImage);
    int rows_1 = getNoOfRows_Image(inputImage2);
    int cols_1 = getNoOfCols_Image(inputImage2);
    int n = rows * cols;
    unsigned no_of_bands;
    no_of_bands = getNoOfBands_Image(inputImage);
    int band = 0;

    for (int bands = 0; bands < no_of_bands; bands++) {
        float error = 0;
        image = getData_Image(inputImage, bands);
        image2 = getData_Image(inputImage2, bands);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                error += pow((image[i][j] - image2[i][j]), 2);

            }
        }
       
        float rmse = sqrt(error / n);
        print_CVIP("\tRms Error %f\n", rmse);
        
    }
    return;
}

float peak_snr(Image* inputImage, Image* inputImage2) {

    byte** image;
    byte** image2;
    unsigned int bands;

    int rows = getNoOfRows_Image(inputImage);
    int cols = getNoOfCols_Image(inputImage);
    int rows_1 = getNoOfRows_Image(inputImage2);
    int cols_1 = getNoOfCols_Image(inputImage2);
    int n = rows * cols;
    unsigned no_of_bands;
    no_of_bands = getNoOfBands_Image(inputImage);
    int band = 0;

    for (int bands = 0; bands < no_of_bands; bands++) {
        float error = 0;
        image = getData_Image(inputImage, bands);
        image2 = getData_Image(inputImage2, bands);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                error += pow((image[i][j] - image2[i][j]), 2);
            }
        }
        float psnr = 10 * log10(255 * 255 / (error / n));
        print_CVIP("\tPeak SNR Error %f\n", psnr);
    }
    return;
}
float rms_snr(Image* inputImage, Image* inputImage2) {

    byte** image;
    byte** image2;
    unsigned int bands;

    int rows = getNoOfRows_Image(inputImage);
    int cols = getNoOfCols_Image(inputImage);
    int rows_1 = getNoOfRows_Image(inputImage2);
    int cols_1 = getNoOfCols_Image(inputImage2);
    int n = rows * cols;
    unsigned no_of_bands;
    no_of_bands = getNoOfBands_Image(inputImage);
    int band = 0;

    for (int bands = 0; bands < no_of_bands; bands++) {
        float error = 0;
        float p = 0;
        image = getData_Image(inputImage, bands);
        image2 = getData_Image(inputImage2, bands);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                error += pow((image[i][j] - image2[i][j]), 2);
                p += pow(image2[i][j],2);

            }
        }

        float rmssnr = sqrt(p / error);
        print_CVIP("\tRMS SNR is %f\n", rmssnr);
    }
    return;
}