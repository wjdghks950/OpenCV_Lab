#include "cv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat img(720, 1080, CV_8UC3, Scalar(0, 0, 255));

	img = imread("lena.png");

	int i, j;

	for (i = 50; i < 100; i++) {
		for (j = 50; j < 100; j++)
		{
			img.at<Vec3b>(i, j)[0] = 0;
			img.at<Vec3b>(i, j)[1] = 0;
			img.at<Vec3b>(i, j)[2] = 255;
		}
	}

	imshow("lenaROI", img);

	unsigned int a = img.at<Vec3b>(50, 50)[2]; //Print the value of red pixel(channel)
	cout << "img.at value is: " << a << endl;

	waitKey(0);

}