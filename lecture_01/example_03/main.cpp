#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
	//Видео поток с подключенной камеры
	VideoCapture cap(0);

	while(true) {
		Mat image;
		//Циклическое получение новых кадров
		cap.read(image);

		//Создание изображения для вывода
		Mat resultImage(image.size(), CV_8U, Scalar(0));

		//Цветовой фильтр
		for (int x = 0; x < image.size().width; x++) {
			for (int y = 0; y < image.size().height; y++) {
				Vec3b pixel = image.at<Vec3b>(y, x);
				uchar blue  = pixel.val[0];
				uchar green = pixel.val[1];
				uchar red   = pixel.val[2];

				if (red > 100) {
				//if (red > 100 && blue < 50 && green < 50) {
					resultImage.at<uchar>(y, x) = 255;
				}
			}
		}

		imshow("resultImage", resultImage);
		imshow("image", image);
		char key = waitKey(1);

		//Прерывание выполнения
		if (key == 27) {
			break;
		}
	}


	return 0;
}
