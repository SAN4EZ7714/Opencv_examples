#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
	Mat ad        = imread( "../../res/ad.jpg", CV_LOAD_IMAGE_COLOR );
	Mat billboard = imread( "../../res/billboard.jpg", CV_LOAD_IMAGE_COLOR );

	imshow("ad", ad);
	imshow("billboard", billboard);
	waitKey(0);

	//Масштабирование изображения которое мы будем накладывать
	resize(ad, ad, Size(467, 152));
	//Получение ROI основного изображение
	Mat billboardCrop = billboard(Rect(65, 144, 467, 152));
	//Копирование содержимого из одной матрицы в другую
	ad.copyTo(billboardCrop);

	imshow("billboardCrop", billboardCrop);
	imshow("merge", billboard);
	waitKey(0);

	return 0;
}
