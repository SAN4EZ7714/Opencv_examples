#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
	VideoCapture cap(0);
	cap.set(CV_CAP_PROP_FRAME_WIDTH,640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);

	while(true) {
		Mat image;
		cap.read(image);

		Mat grayImg;
		cvtColor(image, grayImg, CV_BGR2GRAY);

		Mat gradX, gradY;
		Mat absGradX, absGradY;
		Mat grad;

		/// Градиент X
		Sobel( grayImg, gradX, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT );
		convertScaleAbs( gradX, absGradX );

		/// Градиент Y
		Sobel( grayImg, gradY, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT );
		convertScaleAbs( gradY, absGradY );

		/// Суммирование
		addWeighted( absGradX, 0.5, absGradY, 0.5, 0, grad );

		//Легкое разымытие
		blur(grad, grad, Size(3, 3));

		double minVal, maxVal;
		minMaxLoc(grad, &minVal, &maxVal);

		putText(image, std::to_string(maxVal), Point(50, 50), FONT_HERSHEY_SCRIPT_SIMPLEX, 2, Scalar(0, 0), 4);
		putText(image, std::to_string(maxVal), Point(50, 50), FONT_HERSHEY_SCRIPT_SIMPLEX, 2, Scalar(0, 255), 2);

		imshow("image", image);
		imshow("grad", grad);
		
		char key = waitKey(1);
		if (key == 27) {
			break;
		}
	}


	return 0;
}
