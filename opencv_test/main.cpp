#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(void)
{
	Mat grayim(600, 800, CV_8UC1);
	Mat colorim(600, 800, CV_8UC3);

	for(int i = 0; i < grayim.rows; i++)
		for(int j = 0; j < grayim.cols; j++)
			grayim.at<uchar>(i, j) = (i + j) % 256;
	for (int i = 0; i < colorim.rows; i++)
		for (int j = 0; j < colorim.cols; j++)
		{
			Vec3b pixel;
			pixel[0] = 0;
			pixel[1] = 0;
			pixel[2] = 255;
			colorim.at<Vec3b>(i, j) = pixel;
		}
	while (true)
	{
		imshow("Gray Image", grayim);
		imshow("Color Image", colorim);
		if (waitKey(30) >= 0) break;
	}
}
