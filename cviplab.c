/* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
*
* =========================================================================
*
*             File Name: CVIPlab.c
*           Description: This  is the skeleton program for the Computer Vision
*			 and Image Processing Labs
*   Initial Coding Date: April 23, 1996
*   Last update Date: Jan31, 2017
*   .NET version:     September 21, 2006
*           Portability: Standard (ANSI) C
*             Credit(s): Scott Umbaugh, Zhen Li, Kun Luo,Dejun Zhang,Wenjun(Evan) Bian, Rohini Dahal, Norsang Lama
*                        Southern Illinois University Edwardsville
*  Copyright (C) 2004 Scott Umbaugh and SIUE
*
*  Permission to use, copy, modify, and distribute this software and its
*  documentation for any non-commercial purpose and without fee is hereby
*  granted, provided that the above copyright notice appear in all copies
*  and that both that copyright notice and this permission notice appear
*  in supporting documentation.  This software is provided "as is"
*  without express or implied warranty.
*
****************************************************************************/

/*
** include header files
*/

#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPlab.h"
#include <CVIPtoolkit.h>
#include <CVIPimage.h>
#include <CVIPdef.h>
#include <CVIPspfltr.h>
#include <CVIPconvert.h>
#include <CVIPview.h>
#include <CVIPmap.h>
#include "hist_thresh.h"
#include "CVIPtransform.h"
#include <CVIPspfltr.h>
#include "CVIPtools.h"
#include <CVIPimage.h>
#include <CVIPconvert.h>
#include <CVIPview.h>
#include "histogram.h"
#include "CVIPhisto.h"
#include "CVIParithlogic.h"





//#include "CVIPview.h"

#define CASE_MAX 20

/* Put the command here, as VIDEO_APP, to run your image acquisition
application program */

#define VIDEO_APP "explorer.exe"

/*
** function declarations
*/

Image *threshold_Setup(Image *inputImage);
Image* crop_setup(Image* inputImage);
Image* zoom_setup(Image* inputImage);
Image* dilation_setup(Image* inputImage);
Image* erosion_setup(Image* inputImage);
Image* opening_setup(Image* inputImage);
Image* closing_setup(Image* inputImage);
Image* fft_setup(Image* inputImage);
Image* ideal_setup(Image* inputImage);
Image* unsharp_masking(Image* inputImage);
Image *input();
/*
** start main funct
*/
void main_cviplab() {
	IMAGE_FORMAT  format;     	/* the input image format */
	Image	  *cvipImage; 	/* pointer to the CVIP Image structure */
	Image	  *cvipImage1; 	/* pointer to the CVIP Image structure */
	char	  *outputfile;	/* output file name */
	int		  choice;
	CVIP_BOOLEAN  done = CVIP_NO;
	unsigned int r_c, c_c;
	int conv, conc;

	
	print_CVIP("\n\n\n\n***************************************");
	print_CVIP("****************************  ");
	print_CVIP("\n*\t\t Computer Vision and Image Processing Lab\t  *");
	print_CVIP("\n*\t\t\t <Shivam Jha> \t\t  *");
	print_CVIP("\n******************************************");
	print_CVIP("*************************\n\n\n");

	while (!done) {
		print_CVIP("\t\t0.\tExit \n");
		print_CVIP("\t\t1.\tGrab and Snap an Image  \n");
		print_CVIP("\t\t2.\tThreshold Operation\n");
		print_CVIP("\t\t3.\tCrop  \n");
		print_CVIP("\t\t4.\tZoom  \n");
		print_CVIP("\t\t5.\tArea  \n");
		print_CVIP("\t\t6.\tEuler  \n");
		print_CVIP("\t\t7.\tSobel \n");
		print_CVIP("\t\t8.\tRoberts \n");
		print_CVIP("\t\t9.\tHistogram Thresholding \n");
		print_CVIP("\t\t10.\tDilation  \n");
		print_CVIP("\t\t11.\tErosion  \n");
		print_CVIP("\t\t12.\tOpening  \n");
		print_CVIP("\t\t13.\tClosing \n");
		print_CVIP("\t\t14.\tRMS \n");
		print_CVIP("\t\t15.\tPeak SNR \n");
		print_CVIP("\t\t16.\tRMS SNR \n");
		print_CVIP("\t\t17.\tFFT Transform \n");
		print_CVIP("\t\t18.\tIdeal Filters \n");
		print_CVIP("\n\nCVIPlab>>");



		/*
		** obtain an integer between 0 and CASE_MAX from the user
		*/
		choice = getInt_CVIP(10, 0, CASE_MAX);

		switch (choice) {

		case 0:
			done = CVIP_YES;
			break;

		case 1:
			if (ShellExecute(NULL, "Open", VIDEO_APP, NULL, NULL, SW_SHOW) <= 32)
				print_CVIP("Error while running Video Program");
			break;

		case 2:
			/*Get the input image */
			cvipImage = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}

			/* calls the threshold function */
			cvipImage = threshold_Setup(cvipImage);
			if (!cvipImage)
			{
				error_CVIP("main", "threshold fails");
				break;
			}

			/*
			** display the resultant image
			*/
			
			view_Image(cvipImage, "threshold");
		
			delete_Image(cvipImage);

			break;

		case 3:
			cvipImage = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}

			/* calls the threshold function */
			cvipImage = crop_setup(cvipImage);
			if (!cvipImage)
			{
				error_CVIP("main", "crop fails");
				break;
			}

			/*
			** display the resultant image
			*/

			view_Image(cvipImage, "crop");

			delete_Image(cvipImage);

			break;
		case 4:
			cvipImage = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}

			/* calls the threshold function */
			cvipImage = zoom_setup(cvipImage);
			if (!cvipImage)
			{
				error_CVIP("main", "zoom fails");
				break;
			}

			/*
			** display the resultant image
			*/

			view_Image(cvipImage, "crop");

			delete_Image(cvipImage);

			break;
		case 5:
			cvipImage = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}

			
			area_lab(cvipImage, &r_c, &c_c);
			print_CVIP("Center Row : %d \n", r_c);
			print_CVIP("Center Column : %d \n", c_c);

			if (!cvipImage)
			{
				error_CVIP("main", "area fails");
				break;
			}

			/*
			** display the resultant image
			*/

			view_Image(cvipImage, "area");

			delete_Image(cvipImage);

			break;
		case 6:
			cvipImage = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}

			euler_lab(cvipImage,&conv, &conc);
			print_CVIP("Euler NUmber of the Image is : %d \n",conv-conc);

			if (!cvipImage)
			{
				error_CVIP("main", "Euler fails");
				break;
			}

			/*
			** display the resultant image
			*/

			view_Image(cvipImage, "area");

			delete_Image(cvipImage);

			break;
		case 7:
			cvipImage = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}
		
			
			

			cvipImage = sobel_edge_lab(cvipImage);

			if (!cvipImage)

			{
				error_CVIP("main", "Euler fails");
				break;
			}

			/*
			** display the resultant image
			*/

			view_Image(cvipImage, "sobel");

			delete_Image(cvipImage);

			break;

		case 8:
			cvipImage = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}

			int x;
			print_CVIP("\n\t\tEnter 0 for the 1st approch or enter 1 for 2nd approch : ");
			x = getInt_CVIP(10, 0, 1);
			cvipImage = roberts_edge_lab(cvipImage, x);
			if (!cvipImage)
			{
				error_CVIP("main", "Roberts fails");
				break;
			}

			/*
			** display the resultant image
			*/

			view_Image(cvipImage, "roberts");

			delete_Image(cvipImage);

			break;

		case 9:
			cvipImage = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}
			print_CVIP("\n\t\tEnter Gaussian standard deviation: ");
			
			cvipImage = hist_thresh_segment(cvipImage,6);
			if (!cvipImage)
			{
				error_CVIP("main", "Thresholding fails");
				break;
			}

			/*
			** display the resultant image
			*/

			view_Image(cvipImage, "Histogram Thresholding");

			delete_Image(cvipImage);

			break;
		case 10:
			cvipImage = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}
			

			cvipImage = dilation_setup(cvipImage);
			if (!cvipImage)
			{
				error_CVIP("main", "dilation fails");
				break;
			}

			/*
			** display the resultant image
			*/

			view_Image(cvipImage, "Dilation");

			delete_Image(cvipImage);

			break;
		case 11:
			cvipImage = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}


			cvipImage = erosion_setup(cvipImage);
			if (!cvipImage)
			{
				error_CVIP("main", "erosion fails");
				break;
			}

			/*
			** display the resultant image
			*/

			view_Image(cvipImage, "erosion");

			delete_Image(cvipImage);

			break;
		case 12:
			cvipImage = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}


			cvipImage = opening_setup(cvipImage);
			if (!cvipImage)
			{
				error_CVIP("main", "opening fails");
				break;
			}

			/*
			** display the resultant image
			*/

			view_Image(cvipImage, "opening");

			delete_Image(cvipImage);

			break;
		case 13:
			cvipImage = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}


			cvipImage = closing_setup(cvipImage);
			if (!cvipImage)
			{
				error_CVIP("main", "closing fails");
				break;
			}

			/*
			** display the resultant image
			*/

			view_Image(cvipImage, "closing");

			delete_Image(cvipImage);

			break;

		case 14:
			cvipImage = input();
			cvipImage1 = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}
			rmserror(cvipImage, cvipImage1);
			if (!cvipImage)
			{
				error_CVIP("main", "RMS Error");
				break;
			}

			/*
			** display the resultant image
			*/


			delete_Image(cvipImage);

			break;
		case 15:
			cvipImage = input();
			cvipImage1 = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}
			peak_snr(cvipImage, cvipImage1);
			if (!cvipImage)
			{
				error_CVIP("main", "Peak SNR fails");
				break;
			}

			delete_Image(cvipImage);

			break;
		case 16:
			cvipImage = input();
			cvipImage1 = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}
			rms_snr(cvipImage, cvipImage1);
			if (!cvipImage)
			{
				error_CVIP("main", "RMS SNR");
				break;
			}


			delete_Image(cvipImage);

			break;
		case 17:
			cvipImage = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}
			cvipImage = fft_setup(cvipImage);
			
			
			if (!cvipImage)
			{
				error_CVIP("main", "FFT");
				break;
			}

			view_Image(cvipImage, "FFT");

			delete_Image(cvipImage);

			break;
		case 18:
			cvipImage = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}
			cvipImage = ideal_setup(cvipImage);


			if (!cvipImage)
			{
				error_CVIP("main", "Ideal FIlter");
				break;
			}

			view_Image(cvipImage, "Ideal Filter");

			delete_Image(cvipImage);

			break;
		case 19:
			cvipImage = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}
			cvipImage = spatial_lowpass(cvipImage);


			if (!cvipImage)
			{
				error_CVIP("main", "Ideal FIlter");
				break;
			}

			view_Image(cvipImage, "Ideal Filter");

			delete_Image(cvipImage);

			break;
		case 20:
			cvipImage = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}
			cvipImage = meanfilter(cvipImage);


			if (!cvipImage)
			{
				error_CVIP("main", "Ideal FIlter");
				break;
			}

			view_Image(cvipImage, "Ideal Filter");

			delete_Image(cvipImage);

			break;
		
		case 21:
			cvipImage = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}
			cvipImage = unsharp_masking(cvipImage);


			if (!cvipImage)
			{
				error_CVIP("main", "Ideal FIlter");
				break;
			}

			view_Image(cvipImage, "Ideal Filter");

			delete_Image(cvipImage);

			break;
		case 22:
			cvipImage = input();
			if (cvipImage == NULL)
			{
				error_CVIP("main", "could not read input image");
				break;
			}
			cvipImage = meanfilter(cvipImage);


			if (!cvipImage)
			{
				error_CVIP("main", "Ideal FIlter");
				break;
			}

			view_Image(cvipImage, "Ideal Filter");

			delete_Image(cvipImage);

			break;

		default:
			print_CVIP("Sorry ! You Entered a wrong choice ");
			break;
		}
	}
}
/*
** end of the function main
*/


/*
** The following function reads in the image file specified by the user,
** stores the data and other image info. in a CVIPtools Image structure,
** and displays the image.
*/

Image* input() {
	char  		*inputfile;
	Image		*cvipImage;

	/*
	** get the name of the file and stores it in the string 'inputfile '
	*/
	print_CVIP("\n\t\tEnter the Input File Name:  ");
	inputfile = getString_CVIP();

	/*
	** creates the CVIPtools Image structure from the input file
	*/
	cvipImage = read_Image(inputfile, 1);
	if (cvipImage == NULL) {
		error_CVIP("init_Image", "could not read image file");
		free(inputfile);
		return NULL;
	}

	/*
	** display the source image
	*/
	view_Image(cvipImage, inputfile);

	/*
	**IMPORTANT: free the dynamic allocated memory when it is not needed
	*/
	free(inputfile);

	return cvipImage;
}


/*
** The following setup function asks the threshold value from the user. After
** it gets the threshold value, it will call the threshold_Image() function.
*/

Image *threshold_Setup(Image *inputImage) {
	unsigned int 	threshval;      /* Threshold value */

									/*
									** Gets a value between between 0 and 255 for threshsold
									*/
	print_CVIP("\n\t\tEnter the threshold value:  ");
	threshval = getInt_CVIP(10, 0, 255);

	return threshold_lab(inputImage, threshval);

}

Image *crop_setup(Image *inputImage) {
	unsigned int x, y, row_offset, col_offset;
	print_CVIP("\n\t\t Enter X for upper left: ");
	x = getInt_CVIP(10,0,511);
	print_CVIP("\n\t\tEnter Y for the upper right: ");
	y = getInt_CVIP(10,0,511);
	print_CVIP("\n\t\tRow: ");
	row_offset = getInt_CVIP(10,1,511);
	print_CVIP("\n\t\tCol: ");
	col_offset = getInt_CVIP(10,1,511);
	return croplab(inputImage, x, y, row_offset, col_offset);

}
Image* zoom_setup(Image* inputImage) {
	unsigned int x, y, height, width,zoom_factor;
	print_CVIP("\n\t\tEnter X : ");
	x = getInt_CVIP(10, 0, 511);
	print_CVIP("\n\t\tEnter Y : ");
	y = getInt_CVIP(10, 0, 511);
	print_CVIP("\n\t\tHeight: ");
	height = getInt_CVIP(10, 1, 511);
	print_CVIP("\n\t\tWidth: ");
	width = getInt_CVIP(10, 1, 511);
	print_CVIP("\n\t\tZoom Factor: ");
	zoom_factor = getInt_CVIP(10, 1, 511);
	return zoom_lab(inputImage, x, y, height, width,zoom_factor);


}
Image* dilation_setup(Image* inputImage) {
	int struc[9];

	for (int i = 0; i < 9; i++) {
		printf("Choose element %d of structuring element:\n", i + 1);
		struc[i] = getInt_CVIP(10, 0, 1);
	}
	return dilation_lab(inputImage, struc);

}
Image* erosion_setup(Image* inputImage) {
	int struc[9];

	for (int i = 0; i < 9; i++) {
		printf("Choose element %d of structuring element:\n", i + 1);
		struc[i] = getInt_CVIP(10, 0, 1);
	}
	return erosion_lab(inputImage, struc);

}
Image* opening_setup(Image* inputImage) {
	int struc[9];
	Image* image;

	for (int i = 0; i < 9; i++) {
		printf("Choose element %d of structuring element:\n", i + 1);
		struc[i] = getInt_CVIP(10, 0, 1);
	}
	image = erosion_lab(inputImage, struc);
	return dilation_lab(image, struc);

}
Image* closing_setup(Image* inputImage) {
	int struc[9];
	Image* image;


	for (int i = 0; i < 9; i++) {
		printf("Choose element %d of structuring element:\n", i + 1);
		struc[i] = getInt_CVIP(10, 0, 1);
	}
	image = dilation_lab(inputImage, struc);
	return erosion_lab(image, struc);

}
Image* fft_setup(Image* inputImage) {
	int block_size;
	print_CVIP("\n\t\tEnter Block Size : ");
	block_size = getInt_CVIP(10, 0, 1000);
	Image* magImage = fft_transform(inputImage, block_size);
	return magImage;
}
Image* ideal_setup(Image* inputImage) {
	int block_size;
	print_CVIP("\t\t0.\tIdeal Lowpass \n");
	print_CVIP("\t\t1.\tIdeal Highpass\n\n\n");
	print_CVIP("\t\t\tEnter Choice: ");
	int cutoff;
	Image* resultImg;
	int filters = getInt_CVIP(10, 0, CASE_MAX);
	switch (filters) {
	case 0:
		
		print_CVIP("\n\t\tEnter cutoff Size : ");
		cutoff = getInt_CVIP(10, 0, 1000);
		resultImg = lowpass(inputImage, cutoff);
		break;
	case 1:

		print_CVIP("\n\t\tEnter cutoff Size : ");
		cutoff = getInt_CVIP(10, 0, 1000);
		resultImg = highpass(inputImage, cutoff);
		break;
	default:
		print_CVIP("Sorry ! You Entered a wrong choice ");
		break;
	}
	return resultImg;
}
Image* unsharp_masking(Image* inputImage) {
	Image* img;
	 
	img = spatial_lowpass(inputImage);
	unsigned int histogram[100] = { 0 };
	byte** data = NULL;
	int rows = getNoOfRows_Image(img);
	int cols = getNoOfCols_Image(img);
	int bands = getNoOfBands_Image(img);

	for (unsigned int i = 0; i < bands; i++) {
		data = getData_Image(img, i);

		for (int j = 0; j < rows; j++) {
			for (int k = 0; k, cols; k++) {
				histogram[data[j][k]]++;
			}
		}

	}
	unsigned int cdf[100] = { 0 };
	cdf[0] = histogram[0];
	for (int i = 1; i < 100; i++) {
		cdf[i] = cdf[i - 1] + histogram[i];
	}
	double alpha = 100.0 / (rows * cols);
	for (unsigned int i = 0; i < bands; i++) {
		data = getData_Image(img, i);
		for (int j = 0; j < rows; j++) {
			for (int k = 0; k < cols; k++) {
				int old_pixel = data[j][k];
				int new_pixel = round(alpha * cdf[old_pixel]);
				data[j][k] = (byte)new_pixel;
			}
		}
	}

	Image* subtractImage = subtract_Image(inputImage, img);

	double low = 0.0;
	double high = 0.0;
	printf("Enter low percentage in decimal form: ");
	scanf("&ld", &low);
	printf("Enter high percentage in decimal form: ");
	scanf("&ld", &high);

	Image* resultImage = hist_stretch(subtractImage, low, high, 0.025, 0.025);
	return resultImage;
}