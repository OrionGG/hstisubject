#include <opencv2/opencv.hpp>

using namespace cv;

int main3( int argc, char** argv )
{
	Mat image;
	image = imread(argv[1]);
	Mat integralImage;
	integral(image, integralImage);
	cv::namedWindow( "Integral Image", CV_WINDOW_AUTOSIZE );
	
	cv::imshow( "Original Image", image );
	cv::imshow( "Integral Image", integralImage );
	cv::waitKey(0);
	cv::destroyAllWindows();
	return EXIT_SUCCESS;
}