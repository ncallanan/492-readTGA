//
//  main.c
//  Read TGA
//
//  Created by Jean-Yves Hervé [Local] on 2016-02-03.
//  Copyright © 2016 Jean-Yves Hervé. All rights reserved.
//

#include <stdio.h>
//
#include "fileIO_TGA.h"


#define	kNameFile1	"C:\\Users\\Nathan\\Desktop\\prog01.1\\Prog 01\\Handouts\\Read TGA\\Images\\bottles.tga"
#define	kNameFile2	"C:\\Users\\Nathan\\Desktop\\prog01.1\\Prog 01\\Handouts\\Read TGA\\Output\\out_bottles.tga"


int main(int argc, const char * argv[]) {

	imgData myImg = readTGA(kNameFile1);

	if (myImg.array1D !=NULL)
	{
		if (myImg.imgType == kTGA_COLOR)
			myImg.bytesPerPixel = 3;
		else
			myImg.bytesPerPixel = 1;

	}
	else
	{
		printf( "Generation of image data failed.\n");
		return -1;
	}

	printf("Image read\n");

    //here is where we create a sub image
	imgData subImg = grabSub(&myImg, 0,150,0,150);

	if(myImg.array1D == NULL){
        printf("Generation of sub image failed.\n");
	}

	int outOK = writeTGA(kNameFile2, subImg);

    //free the sub image
	freeImg(&myImg);

	if (outOK == 0)
	{
		printf( "Image written.\n");
	}
	else
	{
		printf( "Output of image data failed.\n");
		return -1;
	}


    return 0;
}
