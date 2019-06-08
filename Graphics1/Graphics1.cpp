// Author: Jiahui Huang from CSCG.
// Modified by Kevin Chen
#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
void swap(int* a, int*b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
float getFraction(float x)
{
	if (x > 0) return x - (int)(x);
	else return x - ((int)(x) + 1);
}
int main(int argc, char** argv) 
{
	const int width = 500;
	const int height = 500;
	cv::Mat img(height, width, CV_8UC3, cv::Scalar(0, 0, 0));
	char in;
	while (true)
	{
		cin >> in;
		switch (in)
		{
		case '1'://bresenham line, no AA
		{
			int x0, y0, x1, y1;
			cin >> x0 >> y0 >> x1 >> y1;
			if (abs(y1 - y0) > abs(x1 - x0)) //slope > 1
			{
				swap(&x0, &y0);
				swap(&x1, &y1);
			}
			if (x0 > x1)
			{
				swap(&x0, &x1);
				swap(&y0, &y1);
			}
			int x, y, dx, dy, e;
			dx = x1 - x0;
			dy = y1 - y0;
			e = -dx;
			x = x0, y = y0;
			for (int i = 0; i<=dx; i++)
			{
				img.at<cv::Vec3b>(y, x)[0] = 255;
				x++;
				e = e + 2 * dy;
				if (e >= 0)
				{
					y++;
					e = e - 2 * dx;
				}
			}
			break;
		}
		case '2': //Xiaolin Wu Anti-aliasing
		{
			int x0, y0, x1, y1;
			cin >> x0 >> y0 >> x1 >> y1;
			int steep = abs(y1 - y0) > abs(x1 - x0);
			if (steep)
			{
				swap(&x0, &y0);
				swap(&x1, &y1);
			}
			if (x0 > x1)
			{
				swap(&x0, &x1);
				swap(&y0, &y1);
			}
			float dx = x1 - x0;
			float dy = y1 - y0;
			float gradient = dy / dx;
			if (dx == 0.0)
				gradient = 1;
			int xPix1 = x0;
			int xPix2 = x1;
			float XY = y0; //intersect Y
			if (steep)
			{
				int x;
				for (x = xPix1; x <= xPix2; x++)
				{
					img.at<cv::Vec3b>(x, (int)(XY))[0] = 255 * getFraction(XY);
					img.at<cv::Vec3b>(x, (int)(XY) - 1)[0] = 255 * (1-getFraction(XY));
					XY += gradient;
				}
			}
			else
			{
				int x;
				for (x = xPix1; x <= xPix2; x++)
				{
					img.at<cv::Vec3b>((int)(XY), x)[0] = 255 * getFraction(XY);
					img.at<cv::Vec3b>((int)(XY) - 1, x)[0] = 255 * (1 - getFraction(XY));
					XY += gradient;
				}
			}
			break;
		}
		default:
			cout << "invalid input\n";
		case 'h':
		{
			cout << "1 - Bresenham no AA\n2 - Xiaolin Wu AA\nq - Quit\n";
			continue;
		}
		case 'q':
			system("pause");
			return 0;
		}



		for (int c = 0; c < width; ++c) {
			img.at<cv::Vec3b>(100, c)[1] = 255;
		}
		// Save the image.
		cv::imwrite("output.png", img);
		// Show the image, wait for user keystroke and quit.
		cv::imshow("output", img);
		cv::waitKey(0);
		cv::destroyAllWindows();
	}
	system("pause");
	return 0;
}