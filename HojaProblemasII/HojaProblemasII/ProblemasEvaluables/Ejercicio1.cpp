#include "..\Header Files\Ejercicio1.h"



bool Ejercicio1::run(const char* filename)
{
	bool bResult = false;

	help();

	Mat image = Global::openImage(filename);

	if(!image.empty()){
		bResult = applyFilters(image);
	}
	else
	{
		cout << ERROROPENFILE << filename;
		bResult = false;
	}
	
	
	return bResult;
}

void Ejercicio1::help()
{
    cout << "Usage: \n"
            "   ./HojaProblemasII Ejercicio1 [filepath]\n";
}

bool Ejercicio1::applyFilters(Mat image)
{
	
	bool bResult = false;
	Mat oOutputArrayA;

	float mKernelA[] = {1.0/16, 2.0/16, 1.0/16,
	2.0/16, 4.0/16, 2.0/16,
	1.0/16, 2.0/16, 1.0/16};
 
	Mat filterA = Mat(3, 3, CV_32FC1, mKernelA);

	clock_t beginA = clock();
	filter2D(image, oOutputArrayA, image.type() , filterA);	
	clock_t endA = clock();
	double elapsed_secsA = double(endA - beginA) / CLOCKS_PER_SEC;
	cout << elapsed_secsA << endl;

	Mat mKernelB1(1, 3, CV_64F);	
	mKernelB1.row(0).col(0) = ((double) 1/4);
	mKernelB1.row(0).col(1) = ((double) 2/4);
	mKernelB1.row(0).col(2) = ((double) 1/4);
	//mKernelB1.at<double>(0,0) = 1/4;
	//mKernelB1.at<double>(0,1) = 2/4;
	//mKernelB1.at<double>(0,2) = 1/4;

	
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