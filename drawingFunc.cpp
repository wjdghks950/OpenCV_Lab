#include "cv.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("lena.png");
	Point pt1, pt2, pt3;
	pt1.x = 300, pt1.y = 300;
	pt2.x = 400, pt2.y = 400;
	pt3.x = 150, pt3.y = 100;
	const string str = "Lena";

	rectangle(src, pt1, pt2, Scalar(255, 0, 0), 2, 8, 0); //rectangle() function

	line(src, pt1, pt2, Scalar(0, 0, 255), 2, 10, 0); //line() function

	putText(src, str, pt3, 1, 8.0, Scalar(0, 255, 0), 3, 8); //putText() function

	imshow("RECT", src);
	waitKey(0);
}