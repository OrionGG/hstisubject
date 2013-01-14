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
		char c = (char)waitKey(20);
        if( c == 27 )
            break;
	}
	
	cv::destroyAllWindows();
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



Mat Ejercicio6::getHistogram(vector<Mat> vImages){
	vector<Mat> vResult;
	int bins = 25;
	int histSize = MAX( bins, 2 );

	vector<Mat> vHists = getHistograms(vImages);
	Mat hist;
	merge(vHists, hist);

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
			
		/// Separate the image in 3 places ( B, G and R )
		vector<Mat> bgr_planes;
		split( src, bgr_planes );

		/// Establish the number of bins
		int histSize = 256;

		/// Set the ranges ( for B,G,R) )
		float range[] = { 0, 256 } ;
		const float* histRange = { range };

		bool uniform = true; bool accumulate = false;

		Mat b_hist, g_hist, r_hist, hist;

		/// Compute the histograms:
		calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
		calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
		calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

		// Draw the histograms for B, G and R
		int hist_w = 512; int hist_h = 400;
		int bin_w = cvRound( (double) hist_w/histSize );

		Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

		normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
		normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
		normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
		normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

		vector<Mat> vHistograms;
		vHistograms.push_back(b_hist);
		vHistograms.push_back(g_hist);
		vHistograms.push_back(r_hist);
		merge(vHistograms, hist);

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

	waitKey(20);

	
	bResult = true;
	return bResult;
}
