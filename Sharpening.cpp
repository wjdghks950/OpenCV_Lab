/*This code is an example of unsharp mask filtering
Sharpening the image*/
#include "cv.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat input = imread("lena.png");
	Mat gray, blur, sharp;

	cvtColor(input, gray, CV_BGR2GRAY);

	GaussianBlur(gray, blur, Size(0, 0), 3); //Blurring with Gaussian blur

	addWeighted(gray, 1.5, blur, -0.5, 0, sharp); //Adding a new mask to the original image

	imshow("gray", gray);
	imshow("gaussian", blur);
	imshow("sharpened", sharp);

	waitKey(0);
	destroyAllWindows();

	return 0;

}