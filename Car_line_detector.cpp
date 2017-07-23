/*This code detects lines on the road (Video file extracted from a blackbox within a vehicle*/
#include "cv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture cap("day.avi");
	Mat frame, canny, hough, line_detect, resized, gray, whiteLine, yellowLine, add;

	Scalar y_from(40, 70, 100); //Range for color yellow in HSV
	Scalar y_to(70, 255, 255);

	Rect rect = Rect(300, 230, 400, 200); //For ROI(Region of interest)

	bool stop = false;
	int key = 0;

	while (1)
	{
		if (!stop)
		{
			if (!cap.read(frame)) //Read the frame and check for validity
				break;
			
			resize(frame, resized, Size(1000, 600)); //Resize the frames
			//imshow("FRAME", resized);

			cvtColor(resized, gray, CV_BGR2GRAY);
			cvtColor(resized, yellowLine, CV_BGR2HSV);

			medianBlur(gray, whiteLine, 3); 

			threshold(whiteLine, whiteLine, 140, 255, THRESH_BINARY); //Detect white lines on the road

			inRange(resized, y_from, y_to, yellowLine); //Detect the yellow lines on the road

			imshow("LINE_DETECTION", whiteLine);
			//imshow("YELLOW_LINE", yellowLine); //Yellow line

			//add = whiteLine + yellowLine; //Merging two separate binary videos

			Canny(whiteLine, canny, 50, 200, 3); //Using canny edge detector

			vector<Vec4i>lines;
			HoughLinesP(canny, lines, 1, CV_PI / 180, 80, 30, 10);//Hough tranformation

			/*for (size_t i = 0; i < lines.size(); i++)
			{
				Vec4i l = lines[i];
				line(canny, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3);
			}*/

			Mat roi = canny(rect);

			imshow("ADDED", roi);

			key = waitKey(30);
			if (key == 32)
			{
				if (stop == false)
					stop = true;
				else
					stop = false;
			}
			else if (key == 27) //"ESC" terminates the video
				break;
		}
		else
		{
			key = waitKey(30);
			if (key == 32)
				stop = false;

		}
	}

}