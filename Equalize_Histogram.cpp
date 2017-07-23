/*Histogram equalization is used for image enhancement*/
#include "cv.hpp"

using namespace std;
using namespace cv;

Mat drawHistogram(Mat src);

int main()
{
	Mat image = imread("lena.png"); //Load image from disk
	Mat grayImage;
	Mat hist_image;

	Mat hist_graph;
	Mat hist_equalized_graph;

	if (!image.data) //Check the validity of image
		exit(1);
	cvtColor(image, grayImage, CV_BGR2GRAY);//Convert image to gray scale

	hist_graph = drawHistogram(grayImage);

	equalizeHist(grayImage, hist_image); // Histogram equalization

	hist_equalized_graph = drawHistogram(hist_image);

	imshow("Input Image", image);
	imshow("Gray Image", grayImage);
	imshow("Hist Equalized Image", hist_image);
	imshow("Hist Graph", hist_graph);
	imshow("Hist Equalized Graph", hist_equalized_graph);

	waitKey(0); //Wait for a keystroke
	destroyAllWindows();
	return 0;
}

Mat drawHistogram(Mat src)
{
	//establish the number of bins
	int histSize = 256;

	//set the ranges
	float range[] = { 0, 256 };
	const float* histRange = { range };

	bool uniform = true;
	bool accumulate = false;

	Mat hist;

	//compute the histograms
	calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

	//draw the histogram
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

	//normalize the result to [0, histImage.rows]
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < histSize; i++)
	{
		rectangle(histImage, Point(bin_w*i, hist_h), Point(bin_w*i, hist_h - cvRound(hist.at<float>(i))), Scalar(0, 0, 0), 2, 8, 0);
	}

	return histImage;
}