// XLAV_Lab03.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Blur.h"
#include "EdgeDetector.h"
int main(int argc, char* argv[])
{
	Mat src, dst;

	if (!strcmp(argv[1], "--mean")) {
		if (argc != 5) {
			cout << "Wrong arguments" << endl;
			return 0;
		}
		else {
			src = imread(argv[2]);
			Blur mean;
			if (mean.BlurImage(src, dst, atoi(argv[3]), atoi(argv[4]), MEAN)) {
				cout << "Something wrong." << endl;
				return 0;
			}
		}
	}
	else if (!strcmp(argv[1], "--median")) {
		if (argc != 5) {
			cout << "Wrong arguments" << endl;
			return 0;
		}
		else {
			src = imread(argv[2]);
			Blur median;	
			if (median.BlurImage(src, dst, atoi(argv[3]), atoi(argv[4]), MEDIAN)) {
				cout << "Something wrong." << endl;
				return 0;
			}
		}
	}
	else if (!strcmp(argv[1], "--gauss")) {
		if (argc != 5) {
			cout << "Wrong arguments" << endl;
			return 0;
		}
		else {
			src = imread(argv[2]);
			Blur gauss;
			if (gauss.BlurImage(src, dst, atoi(argv[3]), atoi(argv[4]), GAUSSIAN)) {
				cout << "Something wrong." << endl;
				return 0;
			}
		}
	}
	else if (!strcmp(argv[1], "--sobel")) {
		if (argc != 3) {
			cout << "Wrong arguments" << endl;
			return 0;
		}
		else {
			src = imread(argv[2]);
			EdgeDetector sobel;
			if (sobel.DetectEdge(src, dst, 3, 3, SOBEL)) {
				cout << "Something wrong." << endl;
				return 0;
			}
		}
	}
	else if (!strcmp(argv[1], "--prewitt")) {
		if (argc != 3) {
			cout << "Wrong arguments" << endl;
			return 0;
		}
		else {
			src = imread(argv[2]);
			EdgeDetector prewitt;
			if (prewitt.DetectEdge(src, dst, 3, 3, PREWITT)) {
				cout << "Something wrong." << endl;
				return 0;
			}
		}
	}
	else if (!strcmp(argv[1], "--laplace")) {
		if (argc != 3) {
			cout << "Wrong arguments" << endl;
			return 0;
		}
		else {
			src = imread(argv[2]);
			EdgeDetector laplace;
			if (laplace.DetectEdge(src, dst, 3, 3, LAPLACE)) {
				cout << "Something wrong." << endl;
				return 0;
			}
		}
	}

	imshow("Destination_Image", dst);
	imwrite("Destination_Image.png", dst);
	waitKey(0);

	return 0;
}
