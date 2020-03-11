#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;


Mat src, img, ROI;
Rect Rectangle(0, 0, 0, 0);
Point P1(0, 0);
Point P2(0, 0);

const char* winName = "Draw Rect";
bool clicked = false;
int i = 0;
char imgName[15];


void Boundary() {
	if (Rectangle.width > img.cols - Rectangle.x)
		Rectangle.width = img.cols - Rectangle.x;

	if (Rectangle.height > img.rows - Rectangle.y)
		Rectangle.height = img.rows - Rectangle.y;

	if (Rectangle.x < 0)
		Rectangle.x = 0;

	if (Rectangle.y < 0)
		Rectangle.height = 0;
}

void Image() {
	img = src.clone();
	Boundary();
	if (Rectangle.width > 0 && Rectangle.height > 0) {
		ROI = src(Rectangle);
		imshow("Rectangle", ROI);
	}

	rectangle(img, Rectangle, Scalar(0, 255, 0), 1, 8, 0);
	imshow(winName, img);
}


void Mouse(int event, int x, int y, int f, void*) {

	switch (event) {

	case  EVENT_LBUTTONDOWN:
		clicked = true;

		P1.x = x;
		P1.y = y;
		P2.x = x;
		P2.y = y;
		break;

	case EVENT_LBUTTONUP:
		P2.x = x;
		P2.y = y;
		clicked = false;
		break;

	case  EVENT_MOUSEMOVE:
		if (clicked) {
			P2.x = x;
			P2.y = y;
		}
		break;

	default:   break;


	}
	if (clicked) {
		if (P1.x > P2.x) {
			Rectangle.x = P2.x;
			Rectangle.width = P1.x - P2.x;
		}
		else {
			Rectangle.x = P1.x;
			Rectangle.width = P2.x - P1.x;
		}

		if (P1.y > P2.y) {
			Rectangle.y = P2.y;
			Rectangle.height = P1.y - P2.y;
		}
		else {
			Rectangle.y = P1.y;
			Rectangle.height = P2.y - P1.y;
		}

	}
	Image();
}
int main()
{
	cout << "x to save" <<  endl;
	cout << "w increase top" << endl;
	cout << "s increase bottom" << endl;
	cout << "d increase right" << endl;
	cout << "a increase left" <<  endl;
	cout << "r to reset" << endl;
	cout << "Esc to quit" << endl;
	src = imread("random.png", 1);
	namedWindow(winName, WINDOW_NORMAL);
	setMouseCallback(winName, Mouse, NULL);
	imshow(winName, src);
	while (1) {
		char c = waitKey();
		if (c == 'x'&&ROI.data) {
			sprintf_s(imgName, "%d.jpg", i++);
			imwrite(imgName, ROI);
			cout << "Img  Saved " << imgName << endl;
		}	
		if (c == 'w') { Rectangle.y--; Rectangle.height++; }
		if (c == 'd') Rectangle.width++;
		if (c == 's') Rectangle.height++;
		if (c == 'a') { Rectangle.x--; Rectangle.width++; }
		if (c == 10) break;
		if (c == 'r') { Rectangle.x = 0; Rectangle.y = 0; Rectangle.width = 0; Rectangle.height = 0; }
		Image();

	}
	return 0;
}