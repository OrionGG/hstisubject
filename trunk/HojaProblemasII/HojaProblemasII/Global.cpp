#include "Header Files\Global.h"



Mat Global::openImage(const char*  sImageFile){
	const char* filename = "..\\Images\\lineas5.jpg";			
	
	Mat src;
	try
	{
		src = imread(filename);
	}
	catch(Exception ex)
	{		
		filename = sImageFile;
		src = imread(filename);
	}

	return src;
}