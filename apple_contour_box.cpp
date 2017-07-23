#include "cv.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("apple.jpg");

	Mat gray, range, hsv, range2;
	Scalar from(110, 0, 30); //Range of red
	Scalar to(130, 255, 245);
	vector<Mat> planes(3);

	Size size(3, 3);
	Mat kernel = getStructuringElement(MORPH_ELLIPSE, size);

	Point anchor(-1, 1);
	Mat con;
	Mat element(5, 5, CV_8U, Scalar(1));

	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;

	int num_con;

	//Converting img to HSV for more accurate red color
	cvtColor(img, hsv, CV_RGB2HSV);

	//Extracting mask for red
	inRange(hsv, from, to, range);

	//Eroding & dilating removes small dots/noises
	erode(range, kernel, Mat(), Point(-1, -1), 3);

	dilate(kernel, range2, Mat(), Point(-1, -1), 5);

	//Close using morphologyEx(enlarges the whiter part)
	morphologyEx(range2, range2, MORPH_CLOSE, element);

	//Finding contours(lines) and draw rectangles around the contours
	findContours(range2, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<Rect> rect(contours.size());

	//Drawing rectangles around the contours
	for (int i = 0; i < contours.size(); i++)
		rect[i] = boundingRect(Mat(contours[i]));
	for (int i = 0; i < contours.size(); i++)
		rectangle(img, rect[i], 0, 2, 8, 0); //Draw the boxes on the original image

	num_con = contours.size();
	string c = to_string(num_con);
	putText(img, "Number of apples:" , Point(50, 60), 1, 2, Scalar(255, 255, 0), 3, 8, false);
	putText(img, c, Point(365, 63), 1, 2, Scalar(255, 255, 0), 3, 8, false);

	imshow("ORIGINAL", img);

	imshow("MASK", range2);

	waitKey(0);
	destroyAllWindows();

	return 0;
}