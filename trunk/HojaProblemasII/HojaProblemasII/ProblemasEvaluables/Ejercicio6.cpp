#include "..\Header Files\Ejercicio6.h"

bool Ejercicio6::run(char* pathname )
{
	bool bResult = false;
	help();

	listDirectoryWithSkinImages(pathname);


	
	return bResult;
}

void Ejercicio6::help()
{
    cout << "\nUsage: \n"
            "   ./HojaProblemasII Ejercicio6 [pathname] [camera number]\n";
}

void Ejercicio6:: listDirectoryWithSkinImages(char* dir)
{
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
			processFile((char*)sFullPath.c_str());
		}
    }
}

bool Ejercicio6::processFile(const char* filename)
{
	bool bResult = false;
	Mat src;
	src = Global::openImage(filename);

	if(!src.empty()){
		bResult = detectSkin(src);
	}
	else
	{
		cout << ERROROPENFILE << filename;
		bResult = false;
	}
	return bResult;
}


bool Ejercicio6::detectSkin(Mat src){
	bool bResult = false;
	Mat dst;


	if( !src.data )
	{ return bResult; }

	/// Separate the image in 3 places ( B, G and R )
	vector<Mat> bgr_planes;

	split( src, bgr_planes );

	/// Establish the number of bins
	int histSize = 256;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 } ;
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat b_hist, g_hist, r_hist;

	/// Compute the histograms:
	calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
	calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
	calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

	// Draw the histograms for B, G and R
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound( (double) hist_w/histSize );

	Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

	/// Draw for each channel
	for( int i = 1; i < histSize; i++ )
	{
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
			Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
			Scalar( 255, 0, 0), 2, 8, 0  );
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
			Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
			Scalar( 0, 255, 0), 2, 8, 0  );
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
			Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
			Scalar( 0, 0, 255), 2, 8, 0  );
	}

	/// Display
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
	imshow("calcHist Demo", histImage );

	/// Get Backprojection
	MatND backproj;
	calcBackProject(&bgr_planes[0], 1, 0, b_hist, backproj, &histRange, 1, true );

	/// Draw the backproj
	imshow( "BackProj", backproj );

	waitKey(0);


	return bResult;
}
