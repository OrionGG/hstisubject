#include "Header Files\Global.h"



Mat Global::openImage(const char*  sImageFile){
	const char* filename = "..\\Images\\lineas5.jpg";			
	
	Mat src;
	
	src = imread(filename);
	if( src.empty()){
		filename = sImageFile;
		src = imread(filename);
	}

	return src;
}