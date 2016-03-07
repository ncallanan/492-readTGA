#include <stdio.h>
#include "arrayUtils.h"

int main(){

    //test ivector
    printf("ivector \n");
    int* vector = ivector(2,5);
    for(int i = 0; i < 7; i++){
        vector[i] = i;
    }
    for(int i = 0; i < 5; i++){
        printf("vector[%d] is: %d \n", i, vector[i]);
    }
    free_iVector(vector,2);

    //test matrix
    printf("\ntest matrix \n");
    int** matrix = iMatrix(1,3,1,3);

    for(int i = 1; i < 4; i++){
        for(int j = 0; j < 3; j++){
            matrix[i][j] = i*10 + j;
        }
    }

    for(int i = 1; i < 4; i++){
        for(int j = 0; j < 3; j++){
            printf("myArray2[%d][%d] is %d\n", i, j, matrix[i][j]);
        }
    }
    free_iMatrix(matrix,1,3,1);

}
