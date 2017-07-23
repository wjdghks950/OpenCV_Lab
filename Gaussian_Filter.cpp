/*This code is a simple exmpale of using Gaussian filter in image blur*/
#include "cv.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("lena.png");
	Mat grayScale, blur;

	cvtColor(image, grayScale, CV_BGR2GRAY);

	//GaussianBlur(InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY=0, int borderType);
	GaussianBlur(grayScale, blur, Size(5, 5), 9.0); 

	imshow("GRAY", grayScale);
	imshow("BLUR", blur);

	waitKey(0);
	destroyAllWindows();
	return 0;


}