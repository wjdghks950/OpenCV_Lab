/*This is an example of smoothing filter - using Median blur*/

#include "cv.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat input = imread("lena.png");
	Mat gray, blur;

	if (!input.data)
		exit(0);
	
	cvtColor(input, gray, CV_BGR2GRAY);
	medianBlur(gray, blur, 9); //Using median blur method

	imshow("GRAY", gray);
	imshow("Median Blur", blur);

	waitKey(0);
	destroyAllWindows();
	return 0;
}