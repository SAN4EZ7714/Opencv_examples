#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
	Mat image = imread("../../res/dark.jpg");

	Mat grayImg;
	cvtColor(image, grayImg, CV_BGR2GRAY);

	double minVal, maxVal;
	minMaxLoc(grayImg, &minVal, &maxVal);

	Mat normImg = (image - minVal) * 255 / (maxVal - minVal);
	
	// convertScaleAbs
	// normalize

	imshow("image", image);
	imshow("normImg", normImg);
	
	waitKey(0);

	return 0;
}
