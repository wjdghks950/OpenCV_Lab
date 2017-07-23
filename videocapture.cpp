#include "cv.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat G(1080, 720, CV_8UC1, Scalar(255, 255, 255));
	VideoCapture cap("Jason Bourne 2016 1080p BluRay x264 DTS-JYK.mkv");

	while (1)
	{
		cap >> G;
		imshow("SCREEN", G);
		waitKey(30);
	}
}
