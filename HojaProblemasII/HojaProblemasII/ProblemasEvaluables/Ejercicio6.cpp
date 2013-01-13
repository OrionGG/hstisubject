#include "..\Header Files\Ejercicio6.h"

bool Ejercicio6::run(char* pathname, int iCamNum )
{
	bool bResult = false;
	help();

	vector<Mat> vSkinImages = getSkinImages(pathname);
	Mat oHist = getHistogram(vSkinImages);

	bResult = detectSkinInCamera(oHist, iCamNum);

	bResult = true;
	return bResult;
}

bool Ejercicio6::detectSkinInCamera(Mat oHist, int iCamNum ){
	bool bResult = false;
	VideoCapture cap;
	cap.open(iCamNum);

    if( !cap.isOpened() )
    {
        help();
        cout << "***Could not initialize capturing...***\n";
        cout << "Current parameter's value: " << iCamNum << "\n";
        return bResult;
    }

	
	Mat frame, image;
	for(;;)
    {
        //if( !paused )
        {
            cap >> frame;
            if( frame.empty() )
                break;
        }
		
        frame.copyTo(image);
		detectSkin(image, oHist);
	}
	
	bResult = true;
	return bResult;
}

void Ejercicio6::help()
{
    cout << "\nUsage: \n"
            "   ./HojaProblemasII Ejercicio6 [Directorypath] [camera number/filepath]\n";
}

vector<Mat> Ejercicio6:: getSkinImages(char* dir)
{
	vector<Mat> vResult;
	strcat (dir,"\\");
	string sDirPath = dir;
	WIN32_FIND_DATA findFileData;
    HANDLE          hFind;
 
    strcat (dir,"*");
 
    hFind = FindFirstFile(dir, &findFileData);
 
    if (hFind == INVALID_HANDLE_VALUE)
 	    std::cout << "Ruta incorrecta";
    else
    {
		std::cout << findFileData.cFileName << '\n'; //The first file
 
        // Loop with the others files
        while (FindNextFile(hFind, &findFileData) != 0){
			
			std::cout << findFileData.cFileName << '\n';
			string sFullPath = sDirPath;
			sFullPath += findFileData.cFileName;
			
			std::cout << (char*)sFullPath.c_str() << '\n';

			Mat src = getImage((char*)sFullPath.c_str());
			
			if(src.data){		
				vResult.push_back(src);	
			}
		}
    }
	
	return vResult;
}

Mat Ejercicio6::getImage(const char* filename)
{
	Mat oResult;
	Mat src;
	src = Global::openImage(filename);

	if(!src.empty()){
		oResult = src;
	}
	else
	{
		cout << ERROROPENFILE << filename;
	}
	return oResult;
}

//
//vector<Mat> Ejercicio6::getHistograms(Mat src){
//	vector<Mat> vResult;
//	Mat dst;
//
//
//	if( !src.data )
//	{ return vResult; }
//
//	/// Separate the image in 3 places ( B, G and R )
//	vector<Mat> bgr_planes;
//
//	split( src, bgr_planes );
//
//	/// Establish the number of bins
//	int histSize = 256;
//
//	/// Set the ranges ( for B,G,R) )
//	float range[] = { 0, 256 } ;
//	const float* histRange = { range };
//
//	bool uniform = true; bool accumulate = false;
//
//	Mat b_hist, g_hist, r_hist;
//
//	/// Compute the histograms:
//	calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
//	calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
//	calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );
//	int channels[] = {0, 1, 2};
//	calcHist( &src, 1, channels, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
//
//	// Draw the histograms for B, G and R
//	int hist_w = 512; int hist_h = 400;
//	int bin_w = cvRound( (double) hist_w/histSize );
//
//	Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
//
//	/// Normalize the result to [ 0, histImage.rows ]
//	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
//	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
//	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
//	
//	/// Draw for each channel
//	for( int i = 1; i < histSize; i++ )
//	{
//		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
//			Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
//			Scalar( 255, 0, 0), 2, 8, 0  );
//		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
//			Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
//			Scalar( 0, 255, 0), 2, 8, 0  );
//		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
//			Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
//			Scalar( 0, 0, 255), 2, 8, 0  );
//	}
//
//	/// Display
//	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
//	imshow("calcHist Demo", histImage );
//
//	/// Get Backprojection
//	MatND backproj;
//	//calcBackProject(&bgr_planes[0], 1, 0, b_hist, backproj, &histRange, 1, true );
//
//	//int channels[] = { 0, 1, 2 };
//	//calcBackProject(&bgr_planes[0], bgr_planes.size(), channels, b_hist, backproj, &histRange, 1, true );
//
//
//	/// Draw the backproj
//	//imshow( "BackProj", backproj );
//
//	waitKey(0);
//	
//	vResult.push_back(b_hist);
//	vResult.push_back(g_hist);
//	vResult.push_back(r_hist);
//
//	return vResult;
//}


Mat Ejercicio6::getHistogram(vector<Mat> vImages){
	vector<Mat> vResult;
	int bins = 25;
	int histSize = MAX( bins, 2 );

	vector<Mat> vHists = getHistograms(vImages);
	Mat hist;
	merge(vHists, hist);


	/// Draw the histogram
	int w = 400; int h = 400;
	int bin_w = cvRound( (double) w / histSize );
	Mat histImg = Mat::zeros( w, h, CV_8UC3 );

	if( hist.dims <= 2 && hist.data &&
                 (unsigned)0 < (unsigned)(hist.size.p[0]*hist.size.p[1]) &&
                 hist.elemSize() == CV_ELEM_SIZE(hist.type()) ){
					 int a = 0;
	}

	/*float f = hist.at<float>(0);

	for( int i = 0; i < bins; i ++ )
		{ rectangle( histImg, Point( i*bin_w, h ), Point( (i+1)*bin_w, h - cvRound( hist.at<float>(i)*h/255.0 ) ), Scalar( 0, 0, 255 ), -1 ); }

	imshow( "Histogram", histImg );

	waitKey(0);	*/

	return hist;
}

vector<Mat> Ejercicio6::getHistograms(vector<Mat> vImages){
	vector<Mat> vResult;

	int bins = 25;
	int histSize = MAX( bins, 2 );
	float hue_range[] = { 0, 180 };
	const float* ranges = { hue_range };
	
	for(int i=0; i<vImages.size(); i++){
		Mat src = vImages[i];

		if(!src.data){
			continue;
		}
		
		Mat hsv; Mat hue;
		/// Transform it to HSV
		cvtColor( src, hsv, CV_BGR2HSV );

		/// Use only the Hue value
		hue.create( hsv.size(), hsv.depth() );
		int ch[] = { 0, 0 };
		mixChannels( &hsv, 1, &hue, 1, ch, 1 );
		MatND hist;
		/// Get the Histogram and normalize it
		calcHist( &hue, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false );
		normalize( hist, hist, 0, 255, NORM_MINMAX, -1, Mat() );

		vResult.push_back(hist);

	}

	return vResult;
}

bool Ejercicio6::detectSkin(Mat src, Mat hist){
	bool bResult = false;
	Mat dst;
	vector<Mat> bgr_planes;

	if( !src.data )
	{ return bResult; }


	split( src, bgr_planes );

	/// Establish the number of bins
	int histSize = 256;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 } ;
	const float* histRange = { range };
	
	/// Get Backprojection
	MatND backproj;
	//calcBackProject(&bgr_planes[0], 1, 0, hist, backproj, &histRange, 1, true );

	int channels[] = { 0, 1, 2 };
	calcBackProject(&bgr_planes[0], bgr_planes.size(), channels, hist, backproj, &histRange, 1, true );


	/// Draw the backproj
	
    imshow( "Cam", src );
	imshow( "BackProj", backproj );

	waitKey(2000);
	
	bResult = true;
	return bResult;
}
