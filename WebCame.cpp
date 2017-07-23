#include "cv.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat G(1080, 720, CV_8UC1);
	//capture from webcam
	//whose device number == 0
	VideoCapture cap(0);
	while (1)
	{
		cap >> G;
		imshow("SCREEN", G);
		waitKey(30);
	}
}