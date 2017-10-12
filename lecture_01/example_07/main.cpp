#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
	Mat grayImg = imread("../../res/salary.jpg", 0);

	//Небольшое размытие позволит убрать "шум" от камеры
	blur(grayImg, grayImg, Size(3, 3));

	//Адативный трэшхолд, хорошо выделяет границы
	Mat thresh;
	adaptiveThreshold(grayImg, thresh, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 15, 3);

	//Поиск всех контуров
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours( thresh.clone(), contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

	//Картинка для вывода
	Mat drawing = grayImg.clone();
	cvtColor(drawing, drawing, CV_GRAY2BGR);

	//Удобный герератор рандома
	RNG rng(1);

	int counterCoins = 0;
	int salary = 0;

	//Перебор всех контуров для подсчета монет
	for( int i = 0; i < contours.size(); i++ )
	{
		//Отрисовка всех контуров
		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		drawContours( drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point() );

		//Если контур слишком короткий, то он не может быть монетой
		if (contours[i].size() > 100) {
			//Апроксимируем контур до круга
			Point2f center;
			float radius;
			minEnclosingCircle(contours[i], center, radius);

			bool isCircle = true;

			//Сверяем контур с апроксимированной версией
			for (int c = 0; c < contours[i].size(); c++) {
				Point2f point(contours[i][c].x, contours[i][c].y);
				float dist = norm(point - center);
				if (dist < radius * 0.8 || dist > radius * 1.2) {
					isCircle = false;
					break;
				}
			}

			if (isCircle) {
				counterCoins++;

				//Если радиус больше определенного, то это 5 руб иначе 1 руб
				if (radius > 27.5) {
					salary += 5;
				} else {
					salary += 1;
				}
				circle(drawing, center, radius, Scalar(0, 255), 3);
			}
		}
	}

	std::string text = "Coins: " + std::to_string(counterCoins) + " salary: " + std::to_string(salary);
	putText(drawing, text, Point(50, 50), FONT_HERSHEY_SCRIPT_SIMPLEX, 2, Scalar(0, 0), 4);
	putText(drawing, text, Point(50, 50), FONT_HERSHEY_SCRIPT_SIMPLEX, 2, Scalar(0, 255), 2);

	imshow("drawing", drawing);
	imshow("thresh", thresh);
	imshow("grayImg", grayImg);
	waitKey(0);

	return 0;
}
