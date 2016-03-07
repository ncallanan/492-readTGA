#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//
#include "fileIO_TGA.h"

void swapRGB(imgData *myImg);
unsigned char** ucMatrixFromArray1D(imgData *myImg);
int free_ucScaffoldingMatrix(unsigned char** s,int rowMin);
int freeImg(imgData *myImg);


//----------------------------------------------------------------------
//	Utility function for memory swapping
//	Used because TGA stores the RGB data in reverse order (BGR)
//----------------------------------------------------------------------
void swapRGB(imgData *myImg)
{
	int			imgSize;
	unsigned char tmp;

	imgSize = myImg->nbRows * myImg->nbCols;

	for(int k = 0; k < imgSize; k++)
	{
		tmp = myImg->array1D[k*3+2];
		myImg->array1D[k*3+2] = myImg->array1D[k*3];
		myImg->array1D[k*3] = tmp;
	}
}

//----------------------------------------------------------------------
//  create a 2D matrix from a 1D array
//  Parameter:
//  *myImg - pointer to a struct that defines an image
//----------------------------------------------------------------------
unsigned char** ucMatrixFromArray1D(imgData *myImg)
{
    unsigned char** result = (unsigned char**)calloc((myImg->nbRows),sizeof(unsigned char*));
    result[0] = myImg->array1D;
    for(int i = 1; i < myImg->nbRows; i++){
        result[i] = result[i-1] + 3*myImg->nbCols;
    }
    return result;
}
//----------------------------------------------------------------------
//  given a matrix and starting point, free the data
//----------------------------------------------------------------------
int free_ucScaffoldingMatrix(unsigned char** s,int rowMin)
{
    free(s + rowMin);
    return 0;
}

//----------------------------------------------------------------------
//  Function: grabSub
//  Description:
//      creates a new image struct that taken from specified dimensions of a
//      larger struct
//  Parameters:
//      *myImg - pointer to parent image struct
//      int rowMin, int rowMax - starting x and y coordinates of sub-image
//      int nbRows, int nbCols - width and height of sub-image
//  return: sub image struct
//----------------------------------------------------------------------
imgData grabSub(imgData *myImg, int rowMin, int nbRows, int colMin, int nbCols)
{
    imgData subImage;

    //set sub image values
    subImage.array1D = myImg->array1D;
    subImage.rowMin = rowMin;
    subImage.nbRows = nbRows;
    subImage.colMin = colMin;
    subImage.nbCols = nbCols;
    subImage.imgType= myImg->imgType;

    //adjust starting point for sub image so it is 0 indexed
    subImage.array2D = myImg->array2D + (subImage.rowMin - myImg->rowMin);
    for(int i = 0; i < nbRows; i++){
        subImage.array2D[i] = subImage.array2D[i] + 3*(subImage.colMin - myImg->colMin);
    }

    return subImage;

}

//-----------------------------------------------------------------
//  Utility function to free an image struct
//-----------------------------------------------------------------
int freeImg(imgData *myImg)
{
    //Free 2D
    free_ucScaffoldingMatrix(myImg->array2D,myImg->rowMin);
    //Free 1D
    free(myImg->array1D);
    //Free struct itself
    free(myImg);

    return 0;

}


// ---------------------------------------------------------------------
//	Function : readTGA
//	Description :
//
//	This function reads an imgData of type TGA (8 or 24 bits, uncompressed
//
//  Parameter:
//	*fileName - Pointer to a string that contains the name of the file
//
//	Return value: image struct
//----------------------------------------------------------------------

imgData readTGA(char *fileName)
{
    imgData myImg;
	unsigned char *ptr;
	int		numberOfPixels;
	char	head[18] ;
	FILE	*tga_in;

	/* --- open TARGA input file ---------------------------------- */
	tga_in = fopen(fileName, "rb" );

	if (tga_in == NULL )
	{
		printf("Cannot open pixel file %s \n", fileName);
		myImg.array1D = NULL;
	}

	/* --- Read the header (TARGA file) --- */
	fread( head, sizeof(char), 18, tga_in ) ;
	/* Get the size of the imgData */
	myImg.nbCols = (int)(((unsigned int)head[12]&0xFF) | ((unsigned int)head[13]*256));
	myImg.nbRows = (int)(((unsigned int)head[14]&0xFF) | ((unsigned int)head[15]*256));


	if((head[2] == 2) && (head[16] == 24))
		myImg.imgType = kTGA_COLOR;
	else if((head[2] == 3) && (head[16] == 8))
		myImg.imgType = kTGA_GRAY;
	else
	{
		printf("Unsuported TGA image: ");
		printf("Its type is %d and it has %d bits per pixel.\n", head[2], head[16]);
		printf("The imgData must be uncompressed while having 8 or 24 bits per pixel.\n");
		fclose(tga_in);
		//std::exit(kWrongFileType);
		myImg.array1D = NULL;
	}

	numberOfPixels = myImg.nbCols * myImg.nbRows;
	/* Create the buffer for imgData */

	if (myImg.imgType == kTGA_COLOR)
		myImg.array1D = (unsigned char*) malloc(numberOfPixels*3);
	else
		myImg.array1D = (unsigned char*) malloc(numberOfPixels);

	if(myImg.array1D == NULL)
	{
		printf("Unable to allocate memory\n");
		fclose(tga_in);
		//std::exit(kMemAllocError);
		myImg.array1D = NULL;
	}

	/* Check if the imgData is vertically mirrored */
	if (myImg.imgType == kTGA_COLOR)
	{
		// preallocate an array to store one row.
		unsigned char* oneRow = (unsigned char*) malloc((myImg.nbCols)*3);

		// imgData is written upside down
		if(head[17]&0x20)
		{
		//        --------------------------  end of the array
			ptr = myImg.array1D + numberOfPixels*3 - ((myImg.nbCols)*3);
		//                                     --------------  size of one row
			for(int i = 0; i < myImg.nbRows; i++)
			{
				//          ------------------------ one row worth of data
				fread( ptr, 3*sizeof(char), myImg.nbCols, tga_in ) ;

				// copy oneRow into the data array
				memcpy(ptr, oneRow, (myImg.nbCols)*3);

				ptr -= (myImg.nbCols)*3;
			}

			// delete oneRow
//			free(oneRow);
			free((void*) oneRow);
		}
		else
			//  destination  size of data chunk  number of chunk   source
			fread(myImg.array1D,   3*sizeof(char),    numberOfPixels,    tga_in);

        //  tga files store color information in the order B-G-R
        //  we need to swap the Red and Blue components
    	swapRGB(&myImg);
	}
	else
	{
		if(head[17]&0x20)
		{
			ptr = myImg.array1D + numberOfPixels - myImg.nbCols;
			for(int i = 0; i < myImg.nbRows; i++)
			{
				fread( ptr, sizeof(char), myImg.nbCols, tga_in ) ;
				ptr -= myImg.nbCols;
			}
		}
		else
		fread(myImg.array1D, sizeof(char), numberOfPixels, tga_in);
	}

    //set values for creating 2D raster
	myImg.rowMin = 0;
	myImg.colMin = 0;
	//create 2D raster
	myImg.array2D = ucMatrixFromArray1D(&myImg);

	fclose( tga_in) ;
	return (myImg);
}
//---------------------------------------------------------------------*
//	Function : writeTGA
//	Description :
//
//	 This function write out an imgData of type TGA (24-bit color)
//
//	 Parameters:
//
//	  *fileName - Pointer to a string that contains the name of the file
//	  nbCols, nbRows - Dimensions XxY of the image
//	  *data - pointer to the array containing the pixels. This array
//	          is of type char {r, g, b, r, g, b, ... }
//
//	Return value: Error code (0 = no error)
//----------------------------------------------------------------------*/
int writeTGA(char *fileName, imgData myImg)
{
	int		swapflag = 1;
	char	head[18] ;
	FILE	*tga_out;

	/* --- open TARGA output file ---------------------------------- */

	tga_out = fopen(fileName, "wb" );

	if ( !tga_out )
	{
		printf("Cannot create pixel file %s \n", fileName);
		return(kCannotOpenWrite);
	}

	// --- create the header (TARGA file) ---
	head[0]  = 0 ;		  					// ID field length.
	head[1]  = 0 ;		  					// Color map type.
	head[2]  = 2 ;		  					// imgData type: true color, uncompressed.
	head[3]  = head[4] = 0 ;  				// First color map entry.
	head[5]  = head[6] = 0 ;  				// Color map length.
	head[7]  = 0 ;		  					// Color map entry size.
	head[8]  = head[9] = 0 ;  				// imgData X origin.
	head[10] = head[11] = 0 ; 				// imgData Y origin.
	head[13] = (char) (myImg.nbCols >> 8) ;		// imgData width.
	head[12] = (char) (myImg.nbCols & 0x0FF) ;
	head[15] = (char) (myImg.nbRows >> 8) ;		// imgData height.
	head[14] = (char) (myImg.nbRows & 0x0FF) ;
	head[16] = 24 ;		 					// Bits per pixel.
	head[17] = 0 ;		  					// imgData descriptor bits ;
	fwrite(head, sizeof(char), 18, tga_out );

    //write from a 2D array with 3 values per pixel
	for(int i = 0; i < (myImg.nbRows); i++){
        for(int j = 0; j < (myImg.nbCols); j++){
            fwrite(&(myImg.array2D)[i][3*j+2], sizeof(char), 1, tga_out);
            fwrite(&(myImg.array2D)[i][3*j+1], sizeof(char), 1, tga_out);
            fwrite(&(myImg.array2D)[i][3*j], sizeof(char), 1, tga_out);
        }
	}


	fclose( tga_out ) ;

	return(kNoIOerror);
}


