#include "..\Header Files\Ejercicio4.h"

int Ejercicio4::getMatValue(Mat oMat, int iRow, int iCol){
	int dResult = 0.0;
	
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
	Mat image;
	
	image = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
	
	Mat integralImage;
	integral(image, integralImage);
	double max;
	minMaxIdx(image, 0, &max);
   
	Mat oOutputEdge(image.rows, image.cols, integralImage.type());	
	int iMinRow = -1;
	int iMinCol = -1;
	int iMaxRow = -1;
	int iMaxCol = -1;

	int iMaxValue = 0;
	int iMinValue = 255;
	for(int iRow = 0; iRow < oOutputEdge.rows-1; iRow++){
		for(int iCol = 0; iCol < oOutputEdge.cols-1; iCol++){
			int a = getMatValue(integralImage, iRow, iCol);
			int b = getMatValue(integralImage, iRow, iCol+2);
			int c = getMatValue(integralImage, iRow+2, iCol);
			int d = getMatValue(integralImage, iRow+2, iCol+2);

			int iNewValue = a-b-c+d;
			if(iMaxValue < iNewValue){
				iMaxValue = iNewValue;
				iMaxRow = iRow;
				iMaxCol = iCol;
			}
			if(iNewValue < iMinValue) {
				iMinValue = iNewValue;
				iMinRow = iRow;
				iMinCol = iCol;
			}

			oOutputEdge.row(iRow).col(iCol) = iNewValue;
		}
	}

	oOutputEdge -= iMinValue;

	double dNormalize = ((double)max/(iMaxValue - iMinValue));
	
	oOutputEdge = oOutputEdge * dNormalize;
	
	for(int iCol = 0; iCol < oOutputEdge.cols; iCol++){
		oOutputEdge.row(oOutputEdge.rows-1).col(iCol) = 0;
	}

	for(int iRow = 0; iRow < oOutputEdge.rows; iRow++){		
		oOutputEdge.row(iRow).col(oOutputEdge.cols-1) = 0;
	}
	
	cv::namedWindow( "Original Image", CV_WINDOW_AUTOSIZE );
	cv::imshow( "Original Image", image );	
	cv::namedWindow( "Integral Image", CV_WINDOW_AUTOSIZE );
	cv::imshow( "Integral Image", integralImage );
	
	cv::namedWindow( "Edge", CV_WINDOW_AUTOSIZE);
	cv::imshow( "Edge", oOutputEdge);
	cv::waitKey(0);
	cv::destroyAllWindows();
	
	return bResult;
}