#ifndef EJECERCICIO5_H_
#define EJECERCICIO5_H_
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <iostream>

#include "..\Header Files\Global.h"


using namespace cv;
using namespace std;


class Ejercicio5{
	public:
		static bool run(const char* filename);
		static bool detectLines(Mat oMat);
		static void help();

	private:
};
#endif