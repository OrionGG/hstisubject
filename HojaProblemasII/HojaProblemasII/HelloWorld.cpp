#include <opencv2/opencv.hpp>

int mainH( int argc, char** argv )
{
	cv::Mat image;
	image = cv::imread(argv[1]);
	cv::namedWindow( "Hello CV", CV_WINDOW_AUTOSIZE );
	cv::imshow( "Hello CV", image );
	cv::waitKey(0);
	cv::destroyAllWindows();
	return EXIT_SUCCESS;
}