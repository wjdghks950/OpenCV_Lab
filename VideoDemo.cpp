#include "cv.hpp"

using namespace std;
using namespace cv;

static char* INPUT_WINDOW = "Input Image";
static char* RESULT_WINDOW_Y = "Result Image : Y";
static char* RESULT_WINDOW_CR = "Result Image : Cr";
static char* RESULT_WINDOW_CB = "Result Image : Cb";

int main()
{
	VideoCapture capture("redline.mp4");
	Mat frame, resized, grayImage;
	vector<Mat>channels(3);

	int i = 0;

	bool stop = false;
	char key;

	while (1) //For each loop, read single frame
	{
		if (!stop) {
			//capture >> frame; //Because capture.read(frame) does exactly the same thing
			if (!capture.read(frame)) //Reads in the frame
				break;

			resize(frame, resized, Size(600, 300));//Resize frame to 300x600

			cvtColor(resized, grayImage, CV_BGR2YCrCb);
			split(grayImage, channels);

			imshow(INPUT_WINDOW, resized);
			imshow(RESULT_WINDOW_Y, channels[0]);
			imshow(RESULT_WINDOW_CR, channels[1]);
			imshow(RESULT_WINDOW_CB, channels[2]);

			key = waitKey(10);
			if (key == 32) { //Pause
				if (stop == false) {
					stop = true;
				}
				else
					stop = false;
			}
			else if (key == 27) //"ESC" terminates the video
				break;
		}
		else { //Resume
			key = waitKey(10);
			if (key == 32)
				stop = false;
		}
	}
}