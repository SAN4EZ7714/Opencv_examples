#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
	VideoCapture cap(0);

	while(true) {
		Mat image;
		cap.read(image);

		Mat grayImg;
		cvtColor(image, grayImg, CV_BGR2GRAY);

		double minVal, maxVal;
		minMaxLoc(grayImg, &minVal, &maxVal);

		Mat normImg = (image - minVal) * 255 / (maxVal - minVal);
		
		// convertScaleAbs
		// normalize

		imshow("image", image);
		imshow("normImg", normImg);
		
		char key = waitKey(1);
		if (key == 27) {
			break;
		}
	}


	return 0;
}
