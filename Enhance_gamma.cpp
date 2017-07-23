#include "cv.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("lena.png", IMREAD_GRAYSCALE);
	Mat g_img;

	float gamma = 0.5; //gamma could be 0.3, 0.7, and other values
	unsigned char pix[256];

	for (int i = 0; i < 256; i++) //
	{
		pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
	}

	g_img = img.clone();

	MatIterator_<uchar> it, end;
	for (it = g_img.begin<uchar>(), end = g_img.end<uchar>(); it != end; it++) {
		*it = pix[(*it)];
	}
	
	imshow("gray", img);
	imshow("gammaimg", g_img);

	waitKey();

	return 0;
}