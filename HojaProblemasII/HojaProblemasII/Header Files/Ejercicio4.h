#ifndef EJECERCICIO4_H_
#define EJECERCICIO4_H_
#include <opencv2/opencv.hpp>
#include <iostream>

#include "..\Header Files\Global.h"

using namespace cv;
using namespace std;


class Ejercicio4{
	public:
		static int getMatValue(Mat oMat, int iRow, int iCol);
		static bool run(const char* filename);	
		static void help();
		static bool applyIntegral(Mat image);

	private:
};
#endif