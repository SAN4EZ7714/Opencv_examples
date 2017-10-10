#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
    //Объект в котором будет храниться изображение
    Mat image;
    //Чтение картинки с диска
    image = imread( "../../res/img.jpg", CV_LOAD_IMAGE_GRAYSCALE );

    //Отображение окна с изображением
    imshow("Windows name", image);
    //Показать все окна и ждать нажатия на любую клавишу
    waitKey(0);

    return 0;
}
