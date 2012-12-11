#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main14( int argc, char** argv )
{
	//VideoCapture capture("E:\Movies\Alice in Wonderland[2010]DvDrip[Eng]-FXG\Alice in Wonderland[2010]DvDrip[Eng]-FXG.avi");

	//Mat edges;
 //   namedWindow("edges",CV_WINDOW_AUTOSIZE);
 //   for(;;)
 //   {
 //       Mat frame;
 //       capture >> frame; // get a new frame from camera
 //       //cvtColor(frame, edges, CV_BGR2GRAY);
 //       //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
 //       //Canny(edges, edges, 0, 30, 3);
 //       imshow("edges", frame);
	//	destroyAllWindows();
 //       if(waitKey(30) >= 0) break;
 //   }


 //   // the camera will be deinitialized automatically in VideoCapture destructor
 //   return EXIT_SUCCESS;

	VideoCapture capture(0);
	capture.grab();
	Mat frame;

	capture.retrieve(frame);
	capture.retrieve(frame);
	capture.retrieve(frame);
	capture.retrieve(frame);
	capture.retrieve(frame);
	capture.retrieve(frame);
	Mat edges;
	cvtColor(frame, edges, CV_BGR2GRAY);
	namedWindow("frame",CV_WINDOW_AUTOSIZE);
	cv::createTrackbar("Frames", "frame", 0, 10, NULL);
	imshow("frame", edges);
	waitKey();
	destroyAllWindows();
	return EXIT_SUCCESS;

}