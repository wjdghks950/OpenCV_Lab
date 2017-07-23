#include "cv.hpp"

using namespace std;
using namespace cv;

int main()
{
	VideoCapture cap("day.avi");
	Mat frame, grayImage, resized, canny, rgb_canny;

	bool stop = false;
	int key = 0;

	//read frame
	while (1)
	{
		if (!stop) {
			if (!cap.read(frame)) //Reads in the frame
				break;

			resize(frame, resized, Size(600, 300));//Resize frame to 300x600
			cvtColor(resized, grayImage, CV_BGR2GRAY);

			//Canny edge detector
			Canny(grayImage, canny, 50, 200, 3);

			imshow("Gray", grayImage);
			imshow("Canny", canny);
			cvtColor(canny, rgb_canny, CV_GRAY2BGR);
			imshow("RGB_CANNY", rgb_canny);

			waitKey(10);

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