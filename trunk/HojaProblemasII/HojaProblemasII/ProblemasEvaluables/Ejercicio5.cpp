#include "..\Header Files\Ejercicio5.h"

bool Ejercicio5::run(const char* filename )
{
	bool bResult = false;
	Mat src;

	src = Global::openImage(filename);

	if(!src.empty()){
		bResult = detectLines(src);
	}
	else
	{
		cout << ERROROPENFILE << filename;
		bResult = false;
	}

	return bResult;
}

bool Ejercicio5::detectLines(Mat oSrc){
	bool bResult = false;
	Mat dst, line_dst, cicle_dst;
	Canny( oSrc, dst, 50, 200, 3 );
	cvtColor( dst, line_dst, CV_GRAY2BGR );

	vector<Vec2f> lines;
	HoughLines( dst, lines, 1, CV_PI/180, 100 );

	for( size_t i = 0; i < lines.size(); i++ )
	{
		float rho = lines[i][0];
		float theta = lines[i][1];
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		Point p1(cvRound(x0 + 1000*(-b)), cvRound(y0 + 1000*(a)));
		Point p2(cvRound(x0 - 1000*(-b)), cvRound(y0 - 1000*(a)));
		line( line_dst, p1, p2, Scalar(0,0,255), 3, 8 );
	}


	/// Convert it to gray
	cvtColor( oSrc, cicle_dst, CV_BGR2GRAY );

	vector<Vec3f> circles;

	/// Apply the Hough Transform to find the circles
	HoughCircles(cicle_dst, circles, CV_HOUGH_GRADIENT, 1, dst.rows/8, 200, 100, 0, 0 );

	/// Draw the circles detected
	for( size_t i = 0; i < circles.size(); i++ )
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// circle center
		circle( cicle_dst, center, 3, Scalar(0,255,0), -1, 8, 0 );
		// circle outline
		circle( cicle_dst, center, radius, Scalar(0,0,255), 3, 8, 0 );
	}

	namedWindow( "Source", 1 );
	imshow( "Source", oSrc );

	namedWindow( "Detected Lines", 1 );
	imshow( "Detected Lines", line_dst );


	namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
	imshow( "Hough Circle Transform Demo", cicle_dst );

	waitKey(0);
	
	return bResult;
}
