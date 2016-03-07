#ifndef	FILE_IO_H
#define	FILE_IO_H

typedef enum eimageFileType
{
		kUnknownImageType = -1,
		kTGA_COLOR,				//	24-bit color image
		kTGA_GRAY,
		kPPM,					//	24-bit color image
		kPGM					//	8-bit gray-level image
} eImageFileType;

typedef enum efileErrorCode
{
		kNoIOerror = 0,
		kFileNameNull,
		kFileNotFound,
		kCannotOpenWrite,
		kCannotOpenRead,
		kWrongFileType,
		kUnknownFileType,
		kErrorReading,
		kErrorWriting,
		kEndOfFileError,
		kMemAllocError
} eFileErrorCode;

typedef struct imgData{
    unsigned char*  array1D;
    unsigned char** array2D;
    int rowMin, nbRows, colMin, nbCols, bytesPerPixel;
    eImageFileType  imgType;

}imgData;

#endif
