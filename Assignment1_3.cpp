#include "cv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture capture("redline.mp4");
	Mat frame, resized, grayImage, range, grayConv, notRange, unmask;

	int order;

	bool stop = false;
	double rate = capture.get(CV_CAP_PROP_FPS); //Frame rate
	int delay = 1000 / rate;
	int key = 0;

	Scalar from(0, 0, 50); //Range of red
	Scalar to(60, 60, 255);

	vector<Mat> planes(3);
	vector<Mat> masked(3); //Used for "split"
	bool first = true;

	cout << "Insert order: ";
	cin >> order;

	while(1)
	{
		if(!stop){
			if (!capture.read(frame))
				break;

			resize(frame, resized, Size(600, 300));
			cvtColor(resized, grayImage, CV_BGR2GRAY, 0); //change to grayImage
			imshow("ORIGINAL", resized);
			imshow("GRAY", grayImage);

			resized.copyTo(grayConv); //특정 컬러 추출 영상 base 복사

			inRange(resized, from, to, range); //Mask 생성(i.e. color Red)(filter for red color)


			/*Extracting red using "at" method only*/
			if (order == 1) { //각 split 된 RGB 채널이 range 값에 해당되면 해당 화소를 grayImage 로 변경
				split(resized, planes);
				for (int y = 0; y < range.rows; y++) {
					for (int x = 0; x < range.cols; x++) {
						if (range.at<uchar>(y, x) != 255)
						{
							planes[0].at<uchar>(y, x) = 100;
							planes[1].at<uchar>(y, x) = 100;
							planes[2].at<uchar>(y, x) = 100;
						}
					}
				}
				merge(planes, grayConv);
			}
			/*Extracting red using "Iterator" method only*/
			/*else if (order == 2)
			{

			}

			//Extracting red using "Bit opertor" only
			else //order == 3
			{
				split(frame, planes);
			}*/

			imshow("Isolated_RED", grayConv);


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
