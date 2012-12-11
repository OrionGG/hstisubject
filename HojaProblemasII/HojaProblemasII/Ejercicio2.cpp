#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>

using namespace cv;

void convolveDFT(const Mat& A, const Mat& B, Mat& C)
{
    // reallocate the output array if needed
    //C.create(abs(A.rows - B.rows)+1, abs(A.cols - B.cols)+1, A.type());
	
    Size dftSize;
    // compute the size of DFT transform
	dftSize.width = getOptimalDFTSize(A.cols);
    dftSize.height = getOptimalDFTSize(A.rows);
	C.create(dftSize, A.type());

	

    // allocate temporary buffers and initialize them with 0's
    Mat tempA;
    Mat tempB;

	Mat planesA[] = {Mat_<float>(A), Mat::zeros(dftSize, CV_32F)};
    merge(planesA, 2, tempA);         // Add to the expanded another plane with zeros

	Mat planesB[] = {Mat_<float>(B), Mat::zeros(dftSize, CV_32F)};
    merge(planesB, 2, tempB);         // Add to the expanded another plane with zeros


    // now transform the padded A & B in-place;
    // use "nonzeroRows" hint for faster processing
	dft(tempA, tempA, 0 , dftSize.height);
    dft(tempB, tempB, 0 , dftSize.height);

    // multiply the spectrums;
    // the function handles packed spectrum representations well
    mulSpectrums(tempA, tempB, tempA, 0);

    // transform the product back from the frequency domain.
    // Even though all the result rows will be non-zero,
    // we need only the first C.rows of them, and thus we
    // pass nonzeroRows == C.rows
    //dft(tempA, tempA, DFT_INVERSE + DFT_SCALE, C.rows);
	idft(tempA, C,  DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT    );

    // all the temporary buffers will be deallocated automatically
}


int main2( int argc, char** argv )
{

	Mat image;
	image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	Mat oGaussianDist(image.size(), CV_8U);
	Mat oOutputArray;
	randn(oGaussianDist, Scalar(128), Scalar(20));; // Gaussian dist

	convolveDFT(oGaussianDist, image, oOutputArray);
	
	cv::namedWindow( "Ejecicio2", CV_WINDOW_AUTOSIZE);
	cv::imshow( "Ejecicio2", oOutputArray);

	cv::waitKey(0);
	cv::destroyAllWindows();
	return EXIT_SUCCESS;
}
