/*This code detects people and draws a bounding box around them*/
/*Uses "background subtraction" in order to keep track of the moving objects in the frames*/
#include "cv.hpp"

using namespace std;
using namespace cv;

int main()
{
	VideoCapture cap("extract_in.mp4");
	Mat first_frame, frame, accumulate_frame, bg_subtraction, bg_gray;
	Mat sum_frame(Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH), (int)cap.get(CV_CAP_PROP_FRAME_HEIGHT)), CV_32F, Scalar::all(0));
	Mat bg_frame = imread("Bg_subtraction.jpg");
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

	//Variables for contours
	Mat con;
	Mat element(5, 5, CV_8U, Scalar(1));
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;
	int w_threshold = 40;
	int h_threshold = 60;
	int num_con;

	int fps = (int)(cap.get(CV_CAP_PROP_FPS));
	int delay = 1000 / fps;
	int frameNum = 0;

	bool stop = false;
	int key = 0;

	//Store the first frame(since it does not have any moving object present
	cap >> first_frame;
	//imshow("FIRST_FRAME", first_frame);
	
	while (1) //For each loop, read single frame
	{
		if (!stop) {
			//capture >> frame; //Because capture.read(frame) does exactly the same thing
			if (!cap.read(accumulate_frame)) //Reads in the frame
				break;
			if (accumulate_frame.empty())
				break;

			frame = accumulate_frame.clone();

			cvtColor(accumulate_frame, accumulate_frame, CV_BGR2GRAY);
			accumulate(accumulate_frame, sum_frame);

			//Difference between background frame and current frame
			absdiff(frame, first_frame, bg_subtraction);
			//Convert the difference video to gray scale
			cvtColor(bg_subtraction, bg_gray, CV_BGR2GRAY);
			//Set threshold for the moving objects in the difference video
			threshold(bg_gray, bg_gray, 60, 255, THRESH_BINARY);

			//Blur the binary version to make white more like a blob
			//medianBlur(bg_gray, bg_gray, 7);
			GaussianBlur(bg_gray, bg_gray, Size(5, 5), 1);

			//Dilate to enlarge the white elements of the video
			dilate(bg_gray, bg_gray, Mat(), Point(-1, -1), 12);

			//Erode the video to remove small white spaces
			erode(bg_gray, bg_gray, Mat(), Point(-1, -1), 2);

			//Finding contours(lines)
			findContours(bg_gray, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
			vector<Rect> rect(contours.size());
			
			num_con = 0;
			//Drawing rectangles around the contours
			for (int i = 0; i < contours.size(); i++)
				rect[i] = boundingRect(Mat(contours[i]));
			for (int i = 0; i < contours.size(); i++) {
				if (rect[i].width > w_threshold || rect[i].height > h_threshold)//The size of the contour must be larger than the thresholds
				{
					rectangle(frame, rect[i], 0, 2, 8, 0); //Draw the boxes on the original frame
					num_con++; //Count the number of boxes
				}
			}

			string c = to_string(num_con);

			putText(frame, "Number of people:", Point(200, 200), 1, 2, Scalar(100, 200, 0), 3, 8, false);
			putText(frame, c, Point(520, 200), 1, 2, Scalar(255, 200, 0), 3, 8, false);

			imshow("FRAME", frame);
			//imshow("ACCUMULATED", sum_frame);
			//imshow("DIFF_VIDEO", bg_subtraction);
			imshow("BINARY VIDEO", bg_gray);

			frameNum++; //Increment the number of frame per loop

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
	sum_frame = sum_frame / (float)frameNum;
	imwrite("Bg_subtraction.jpg", sum_frame);

	return 0;
}