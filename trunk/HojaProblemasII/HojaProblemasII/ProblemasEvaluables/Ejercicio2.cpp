#include "..\Header Files\Ejercicio2.h"

///transform A and B matrix with the fourier transfomation, multiply them
void Ejercicio2::Conv2ByFFT(const Mat A, const Mat B, Mat& C)
{
	Mat tempA;
	Mat tempB;

	dft(A, tempA );
	normalize(tempA, tempA, 1.0, 0.0, NORM_MINMAX , CV_32FC1);

    dft(B, tempB );
	normalize(tempB, tempB, 1.0, 0.0, NORM_MINMAX , CV_32FC1);	
	
	C = tempA * tempB;
    //mulSpectrums(tempA, tempB, tempA, 0 );

	idft(C, C);
	 
}

bool Ejercicio2::calculateDFT(Mat image){
	
	bool bResult = false;
	

	int type = image.type();

	if (!( type == CV_32FC1 || type == CV_32FC2 || type == CV_64FC1 || type == CV_64FC2 )){
		normalize(image, image, 1.0, 0.0, NORM_MINMAX , CV_32FC1);
	}
	
	//Gaussian distribution wiht the same size as the input image and same type
	Mat oGaussianDist(image.cols, image.rows,image.type());
	randn(oGaussianDist, Scalar(128), Scalar(20));; // Gaussian dist
	normalize(oGaussianDist, oGaussianDist, 1.0, 0.0, NORM_MINMAX , CV_32FC1);

	
	cv::namedWindow( "image", CV_WINDOW_AUTOSIZE);
	cv::imshow( "image", image);

	Mat oOutputArray;

	Conv2ByFFT(image, oGaussianDist, oOutputArray);
	
	cv::namedWindow( "Ejecicio2", CV_WINDOW_AUTOSIZE);
	cv::imshow( "Ejecicio2", oOutputArray);

	cv::waitKey(0);
	cv::destroyAllWindows();
	return bResult;
}


void Ejercicio2::help()
{
    cout << "Usage: \n"
            "   ./HojaProblemasII Ejercicio2 [filepath]\n";
}



bool Ejercicio2::run(const char* filename)
{	
	bool bResult = false;

	help();

	Mat image = Global::openImage(filename, CV_LOAD_IMAGE_GRAYSCALE);

	if(!image.empty()){
		bResult = calculateDFT(image);
	}
	else
	{
		cout << ERROROPENFILE << filename;
		bResult = false;
	}
	
	return bResult;
}
