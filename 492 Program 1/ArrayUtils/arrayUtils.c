#include <stdlib.h>
#include "arrayUtils.h"


unsigned char* ucvector(int rowMin, int rowMax){
    unsigned char* array =  (unsigned char*) malloc((rowMax-rowMin)*sizeof(unsigned char))- rowMin;
    return array;
}

int* ivector(int rowMin, int rowMax){
    int* array =  (int*) malloc((rowMax-rowMin+1)*sizeof(int))- rowMin;
    return array;
}

unsigned char** ucMatrix(int rowMin,int rowMax,int colMin,int colMax){
    int rowSz = rowMax-rowMin+1;
    int colSz = colMax-colMin+1;
    unsigned char** uc2d = (unsigned char**)malloc(rowSz*sizeof(unsigned char*))-rowMin;
    for(int i = rowMin;i <= rowMax;i++){
        uc2d[i] = (unsigned char*) malloc(colSz*sizeof(unsigned char))-colMin;
    }
    return uc2d;
}

int** iMatrix(int rowMin,int rowMax,int colMin,int colMax){
    int rowSz = rowMax-rowMin+1;
    int colSz = colMax-colMin+1;
    int** i2d = (int**)malloc(rowSz*sizeof(int*))-rowMin;
    for(int i = rowMin;i <= rowMax;i++){
        i2d[i] = (int*) malloc(colSz*sizeof(int))-colMin;
    }
    return i2d;
}

 int free_ucVector(unsigned char* v,int rowMin){
    free(v + rowMin);
    return 0;
}
 int free_iVector(int* v, int rowMin){
    free(v + rowMin);
    return 0;
}

int free_ucMatrix(unsigned char** m, int rowMin,  int rowMax,  int colMin){
    for(int i = rowMin;i <= rowMax;i++){
        free(m[i]);
    }
    free(m + colMin);
    return 0;
}


int free_iMatrix(int** m,int rowMin, int rowMax, int colMin){
    for(int i = rowMin;i <=rowMax;i++){
        free(m[i]);
    }
    free(m + colMin);
    return 0;
}

unsigned char** ucMatrixFromArray1D(unsigned char* a, int rowMin,int rowMax, int colMin, int colMax){
    int rowSz = rowMax-rowMin+1;
	int colSz = colMax-colMin+1;
    unsigned char** ucs2d = (unsigned char**)malloc(rowSz*sizeof(unsigned char*))-rowMin;
    ucs2d[rowMin] = a;
    for(int i = rowMin+1; i <= rowMax; i++){
        ucs2d[i] = ucs2d[i-1] + (colSz);
    }
     for(int i = rowMin+1; i < rowMin+rowSz+1; i++){
        ucs2d[i] = ucs2d[i] - colMin;
    }

    return ucs2d;
}

int** iMatrixFromArray1D(int* a, int rowMin, int rowMax, int colMin, int colMax){
    int rowSz = rowMax-rowMin+1;
	int colSz = colMax-colMin+1;
    int** ucs2d = (int**)malloc(rowSz*sizeof(int*))-rowMin;
    ucs2d[rowMin] = a;
    for(int i = rowMin+1; i <= rowSz; i++){
        ucs2d[i] = ucs2d[i-1] + colSz;
    }
     for(int i = rowMin+1; i < rowMin + rowSz; i++){
        ucs2d[i] = ucs2d[i] - colMin;
    }

    return ucs2d;
}

int free_ucScaffoldingMatrix(unsigned char** m,int rowMin)
{
    free(m + rowMin);
    return 0;
}

int free_iScaffoldingMatrix(int** m,int rowMin)
{
    free(m + rowMin);
    return 0;
}
