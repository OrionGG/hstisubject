#include "..\Header Files\Ejercicio1.h"



bool Ejercicio1::run(const char* filename)
{
	bool bResult = false;


	Mat image;
	image = imread(filename);
	Mat oOutputArrayA;

	
	Mat mKernelA(3, 3, CV_64F);
	mKernelA.row(0).col(0) = ((double) 1/16);
	mKernelA.row(0).col(1) = ((double) 2/16);
	mKernelA.row(0).col(2) = ((double) 1/16);
	mKernelA.row(1).col(0) = ((double) 2/16);
	mKernelA.row(1).col(1) = ((double) 4/16);
	mKernelA.row(1).col(2) = ((double) 2/16);
	mKernelA.row(2).col(0) = ((double) 1/16);
	mKernelA.row(2).col(1) = ((double) 2/16);
	mKernelA.row(2).col(2) = ((double) 1/16);

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
	
	return bResult;
}
