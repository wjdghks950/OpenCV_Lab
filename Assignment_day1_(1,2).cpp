/*This is an assignment code for day1(2017/07/11) of OpenCV camp
#1 Assignment prints gray-scale video
#2 Assignment prints the difference between current and prev frames
#3 Assignment prints a certain color, rendering other colors gray-scale*/

#include "cv.hpp"

using namespace std;
using namespace cv;

int main()
{
	VideoCapture capture("Jason Bourne 2016 1080p BluRay x264 DTS-JYK.mkv");
	Mat frame, grayImage, resized, diff, isolate;
	Mat prev_frame;
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

			cvtColor(resized, grayImage, CV_BGR2GRAY, 0);//Converting the color to gray-scale image

			if (i > 0) { //"i" precludes the first frame
				absdiff(resized, prev_frame, diff);
				imshow("FRAME_DIFF", diff);
			}
			prev_frame = resized.clone(); //store the previous frame(You have to use .clone(), because it might corrupt the "resized")
			i++;

			imshow("SCREEN", resized);
			imshow("GRAY", grayImage);

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