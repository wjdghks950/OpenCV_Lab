#include "cv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

static char* INPUT_WINDOW = "Input Image";
static char* RESULT_WINDOW = "Result Image";
static Mat image, ycrcb; //image and ycrcb are global static variables

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
		cout << "Left button is clicked - position (" << x << " , " << y << ")" << endl;
	else if(event == EVENT_RBUTTONDOWN)
		cout << "Right button is clicked - position (" << x << " , " << y << ")" << endl;
	else if(event == EVENT_MBUTTONDOWN)
		cout << "Middle button is clicked - position (" << x << " , " << y << ")" << endl;
	else if(event == EVENT_MOUSEMOVE)
		cout << "Mouse move over the window - position (" << x << " , " << y << ")" << endl;
	cout << "Pixel value : " << (unsigned int)ycrcb.at<Vec3b>(y, x)[0] << ", " << (unsigned int)ycrcb.at<Vec3b>(y, x)[1] << ", " << (unsigned int)ycrcb.at<Vec3b>(y, x)[2] << ")" << endl;
}

int main()
{
	image = imread("lena.png"); Mat range;
	vector<Mat>channels(3);

	if (image.empty())
	{
		cout << "Error loading the image" << endl;
		return -1;
	}

	//Create a window
	namedWindow("My Window", 1);

	//set the callback function for any mouse event
	setMouseCallback("My Window", CallBackFunc, NULL);

	//Conversion from RGB to YCrCb
	cvtColor(image, ycrcb, CV_BGR2YCrCb);

	//Extracting skin color within the thresholds(lena.png)
	inRange(ycrcb, Scalar(100, 140, 103), Scalar(235, 195, 120), range);

	//Split the Y, Cr, Cb channels
	split(ycrcb, channels);

	//show the image
	imshow("My Window", image);
	imshow("InRange - Skin Color", range);

	waitKey(0);
	return 0;
}