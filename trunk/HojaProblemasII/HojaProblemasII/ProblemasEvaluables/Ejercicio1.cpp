#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <ctime>
#include <iostream>

using namespace cv;
using namespace std;


int main1( int argc, char** argv )
{
	Mat mKernelA;
	mKernelA.push_back((double) 1/16);
	mKernelA.push_back((double) 2/16);
	mKernelA.push_back((double) 1/16);
	mKernelA.push_back((double) 2/16);
	mKernelA.push_back((double) 4/16);
	mKernelA.push_back((double) 2/16);
	mKernelA.push_back((double) 1/16);
	mKernelA.push_back((double) 2/16);
	mKernelA.push_back((double) 1/16);

	Mat image;
	image = imread(argv[1]);
	Mat oOutputArrayA;


	clock_t beginA = clock();
	filter2D(image, oOutputArrayA, image.type() , mKernelA);	
	clock_t endA = clock();
	double elapsed_secsA = double(endA - beginA) / CLOCKS_PER_SEC;
	cout << elapsed_secsA << endl;

	
	Mat mKernelB1(1, 3, CV_64F);	
	mKernelB1.row(0).col(0) = ((double) 1/4);
	mKernelB1.row(0).col(1) = ((double) 2/4);
	mKernelB1.row(0).col(2) = ((double) 1/4);

	
	Mat mKernelB2(3, 1, CV_64F);
	mKernelB2.row(0).col(0) = ((double) 1/4);
	mKernelB2.row(1).col(0) = ((double) 2/4);
	mKernelB2.row(2).col(0) = ((double) 1/4);

	
	Mat oOutputArrayB;

	clock_t beginB = clock();
	sepFilter2D(image, oOutputArrayB, image.type(), mKernelB1, mKernelB2);	
	clock_t endB = clock();
	double elapsed_secsB = double(endB - beginB) / CLOCKS_PER_SEC;
	cout << elapsed_secsB << endl;

	cv::namedWindow( "Ejecicio1A", CV_WINDOW_AUTOSIZE);
	cv::imshow( "Ejecicio1A", oOutputArrayA);

	
	cv::namedWindow( "Ejecicio1B", CV_WINDOW_AUTOSIZE);
	cv::imshow( "Ejecicio1B", oOutputArrayB);

	cv::waitKey(0);
	cv::destroyAllWindows();
	return EXIT_SUCCESS;
}
