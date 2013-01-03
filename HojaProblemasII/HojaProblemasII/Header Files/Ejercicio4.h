#ifndef EJECERCICIO4_H_
#define EJECERCICIO4_H_
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;


class Ejercicio4{
	public:
		static int getMatValue(Mat oMat, int iRow, int iCol);
		static bool run(const char* filename);

	private:
};
#endif