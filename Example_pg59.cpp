#include "cv.hpp"

using namespace std;
using namespace cv;

static char* INPUT_WINDOW = "Input Image";
static char* RESULT_WINDOW_Y = "Result Image : Y";
static char* RESULT_WINDOW_CR = "Result Image : Cr";
static char* RESULT_WINDOW_CB = "Result Image : Cb";

int main()
{
	Mat image = imread("lena.png"); //Load image from the disk
	Mat out;
	vector<Mat>channels(3);

	if (!image.data) {
		printf("No picture\n");
		return -1;
	}

	cvtColor(image, out, CV_BGR2YCrCb);
	split(out, channels);

	imshow(INPUT_WINDOW, image);
	imshow(RESULT_WINDOW_Y, channels[0]);
	imshow(RESULT_WINDOW_CR, channels[1]);
	imshow(RESULT_WINDOW_CB, channels[2]);

	waitKey(0);
	destroyAllWindows();
	return 0;

}