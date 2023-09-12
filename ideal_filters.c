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

Image* lowpass(Image* inputImage, int cutoff)
{
    float** image;
    byte** image2;
    Image* fftImage = fft_transform(inputImage,256);
    int rows = getNoOfRows_Image(fftImage);
    int cols = getNoOfCols_Image(fftImage);
    unsigned no_of_bands;
    no_of_bands = getNoOfBands_Image(fftImage);
    IMAGE_FORMAT format = getFileFormat_Image(fftImage);
    COLOR_FORMAT color = getColorSpace_Image(fftImage);
    CVIP_TYPE cvtype = getDataType_Image(fftImage);
    FORMAT dataformat = getDataFormat_Image(fftImage);

    Image* circle = create_circle(cols, rows, rows / 2, cols / 2, cutoff);
    Image* outputImage;
    outputImage = multiply_Image(fftImage, circle);
    for (int bands = 0; bands < no_of_bands; bands++) {
        
        image = getData_Image(outputImage, bands);
        

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                image[i][j] = log(1 + abs(image[i][j]));
            }
        }

    }
    return outputImage;
}
Image* highpass(Image* inputImage, int cutoff)
{
    float** image;
    byte** image2;
    Image* fftImage = fft_transform(inputImage, 256);
    int rows = getNoOfRows_Image(fftImage);
    int cols = getNoOfCols_Image(fftImage);
    unsigned no_of_bands;
    no_of_bands = getNoOfBands_Image(fftImage);
    IMAGE_FORMAT format = getFileFormat_Image(fftImage);
    COLOR_FORMAT color = getColorSpace_Image(fftImage);
    CVIP_TYPE cvtype = getDataType_Image(fftImage);
    FORMAT dataformat = getDataFormat_Image(fftImage);

    Image* circle = not_Image(create_circle(cols, rows, rows / 2, cols / 2, cutoff));
    Image* outputImage;
    outputImage = multiply_Image(fftImage, circle);
    return outputImage;
}