#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

/**
 * @param rowMin int    first index of array
 * @param rowMax int    last index of array
 * @return unsigned char*
 */
unsigned char* ucVector(int rowMin,int rowMax);
int* iVector(int rowMin,int rowMax);

/**
 * @param rowMin int    first index of 2D
 * @param rowMax int    last index of 2D
 * @param colMin int    first index of the 1D arrays
 * @param colMax int    last index of the 1D arrays
 * @return unsigned char**
 *
 */
unsigned** ucMatrix(int rowMin,int rowMax,int colMin,int colMax);
int** iMatrix(int rowMin,int rowMax,int colMin,int colMax);

/**
 * @param v unsigned char*  vector to free
 * @param rowMin int        start of vector
 * @return int              error code
 */
int free_ucVector(unsigned char* v,int rowMin);
int free_iVector(int* v,int rowMin);

/**
 * @param m unsigned char** matrix to free
 * @param rowMin int        first index of the matrix
 * @param rowMax int        last index of the matrix
 * @param colMin int        start of matrix sub array
 * @return int              error code
 */
int free_ucMatrix(unsigned char** m,int rowMin,int rowMax, int colMin);
int free_iMatrix(unsigned char** m,int rowMin,int rowMax, int colMin);

/**
 * @param a unsigned char*  1D base
 * @param rowMin int        first of 2D
 * @param rowMax int        last of 2D
 * @param colMin int        first of base
 * @param colMax int        last of base
 * @return unsigned char**  2D wrapper array
 */
unsigned char** ucMatrixFromArray1D(unsigned char* a, int rowMin,int rowMax,int colMin,int colMax);
int** iMatrixFromArray1D(int* a, int rowMin,int rowMax,int colMin,int colMax);

/**
 * @param m unsigned char** 2D matrix to free
 * @param rowMin int        first index
 * @return int              error code
 *
 */
int free_ucScaffoldingMatrix(unsigned char** m,int rowMin);
int free_iScaffoldingMatrix(int** m,int rowMin);

#endif	//	ARRAY_UTILS_H
