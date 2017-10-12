#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
	Mat src = imread( "../../res/chess_desk1.jpg", CV_LOAD_IMAGE_COLOR );

	for (int i = 1; ; i++) {
		Mat dstBlur;
		blur(src, dstBlur, Size(i, i));
		
		Mat dstGaussianBlur;
		GaussianBlur(src, dstGaussianBlur, Size(0, 0), i / 3.0f);

		imshow("dstBlur", dstBlur);
		imshow("dstGaussianBlur", dstGaussianBlur);
		char key = waitKey(0);

		//Сбрасываем крэффицент размытития при превышении определенного порога
		if (i == 50) {
			i = 1;
		}

		if (key == 27) {
			break;
		}
	}


	return 0;
}
