#include "cv.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat test;
	test = imread("lena.png", 1);
	uchar * p = test.data;
	for (int i = 0; i < test.cols * test.rows * test.channels(); i++) { //If color, test.cols * test.rows * test.channels
		if (i % 3 == 2)
			p[i] = 255;
	}

	imshow("TEST", test);

	waitKey(0);
}