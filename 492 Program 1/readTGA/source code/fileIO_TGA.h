#ifndef	FILE_IO_TGA_H
#define	FILE_IO_TGA_H

#include "fileIO.h"
/**
*@param *filename char  pointer to string holding name of file
*@return myImg imgData  an image struct
*@see ucMatrixFromArray1D(imgData *myImg)
*@see swapRGB(imgData *myImg)
*/
imgData readTGA(char *fileName);


/**
*@param *filename char  pointer to string holding name of file
*@param  myImg imgData   struct defining aspects of an image
*@return int            error code
*/
int writeTGA(char *fileName, imgData myImg);


/**
*@param *myImg imgData  pointer to struct that stores img info
*@param rowMin int  first row of sub-image
*@param nbRows int  number of rows in sub-image
*@param colMin int  first column of sub-image
*@param nbCols int  number of columns in sub-image
*
*@return subImg imgData returns the sub image struct
*/
imgData grabSub(imgData *myImg, int rowMin, int nbRows, int colMin, int nbCols);

#endif
