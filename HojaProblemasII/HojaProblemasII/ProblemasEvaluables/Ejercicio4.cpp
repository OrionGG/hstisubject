#include "..\Header Files\Ejercicio4.h"

int Ejercicio4::getMatValue(Mat oMat, int iRow, int iCol){
	int dResult = 0;
	
	if((0 <= iRow && iRow < oMat.rows) && (0 <= iCol && iCol < oMat.cols)){
		try
		{    
			dResult = oMat.at<int>(iRow, iCol);
		}
		catch (int e)
		{
			std::cout << "An exception occurred. Exception Nr. " << e << std::endl;
		}
	}

	return dResult;

}

bool Ejercicio4::run(const char* filename )
{
	bool bResult = false;

	help();

	Mat image = Global::openImage(filename, CV_LOAD_IMAGE_GRAYSCALE);

	if(!image.empty()){
		bResult = applyIntegral(image);
	}
	else
	{
		cout << ERROROPENFILE << filename;
		bResult = false;
	}
	
	return bResult;

}

void Ejercicio4::help()
{
    cout << "Usage: \n"
            "   ./HojaProblemasII Ejercicio4 [filepath]\n";
}

bool Ejercicio4::applyIntegral(Mat image){
	bool bResult = false;
	
	Mat integralImage;
	integral(image, integralImage);	
	
	cv::namedWindow( "Original Image", CV_WINDOW_AUTOSIZE );
	cv::imshow( "Original Image", image );	
	cv::namedWindow( "Integral Image", CV_WINDOW_AUTOSIZE );
	cv::imshow( "Integral Image", integralImage );	

	double max;
	minMaxIdx(image, 0, &max);
   
	Mat oIntegralMean(image.rows, image.cols, image.type());	//image.type()); //
	int iMinRow = -1;
	int iMinCol = -1;
	int iMaxRow = -1;
	int iMaxCol = -1;

	int iMaxValue = 0;
	int iMinValue = 255;
	for(int iRow = 1; iRow < oIntegralMean.rows-1; iRow++){
		for(int iCol = 1; iCol < oIntegralMean.cols-1; iCol++){
			int a = getMatValue(integralImage, iRow-1, iCol-1);
			int b = getMatValue(integralImage, iRow-1, iCol+1);
			int c = getMatValue(integralImage, iRow+1, iCol-1);
			int d = getMatValue(integralImage, iRow+1, iCol+1);

			//we calculate the mean value (divide by 4)
			int iNewValue = (a-b-c+d)/4;
			oIntegralMean.row(iRow).col(iCol) = iNewValue;
		}
	}
	
	//diference between the original image and the mean value of the integral image
	Mat oOutputEdge1 = image - oIntegralMean;
	Mat oOutputEdge2 = oIntegralMean - image;


	Mat oOutputEdge = oOutputEdge1 + oOutputEdge2;
	//threshold(oOutputEdge, oOutputEdge, 10, 255, THRESH_BINARY );
	//adaptiveThreshold(oOutputEdge, oOutputEdge, 255, ADAPTIVE_THRESH_MEAN_C , THRESH_BINARY, 7,0);
	threshold(oOutputEdge, oOutputEdge, 0, 255, THRESH_OTSU | THRESH_BINARY );

	cv::namedWindow( "Edge", CV_WINDOW_AUTOSIZE);
	cv::imshow( "Edge", oOutputEdge);
	cv::waitKey(0);
	cv::destroyAllWindows();
	
	return bResult;
}