#ifndef EJECERCICIO2_H_
#define EJECERCICIO2_H_
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>


#include "..\Header Files\Global.h"

using namespace cv;
using namespace std;


class Ejercicio2{
	public:
		static void Conv2ByFFT(Mat A, Mat B, Mat& C);
		static bool calculateDFT(Mat image);	
		static void help();
		static bool run(const char* filename);

	private:
};
#endif