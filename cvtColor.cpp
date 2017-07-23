#include "cv.hpp"

using namespace std;
using namespace cv;
//using cvtColor and split
int main()
{
	Mat src = imread("lena.png", 1);
	Mat result, result_hsv, result_split;
	Mat a[3];
	cvtColor(src, result, CV_BGR2GRAY, 0);
	imshow("GRAY_SCALE", result);
	cvtColor(src, result_hsv, CV_BGR2HSV, 1);
	imshow("HSV", result_hsv);
	split(src, a);
	imshow("SPLIT", a[0]); //Each channel is considered a single-channel, thus "gray-scale"


	waitKey(0);
}