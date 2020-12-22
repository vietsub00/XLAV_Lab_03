#include<iostream>
#include<cmath>

#include"Blur.h"
#include"Convolution.h"
#include"EdgeDetector.h"

int main(int argc, char* argv[])
{
	Mat src = imread("abhishek_gray_noisy.jpg", IMREAD_ANYCOLOR); //IMREAD_GRAYSCALE //IMREAD_ANYCOLOR
	Mat dst1,dst2,dst3;

	Blur edtt;
	edtt.BlurImage(src, dst1, 3, 3, MEDIAN);
	src = dst1;
	edtt.BlurImage(src, dst1, 3, 3, MEDIAN);
	src = dst1;
	edtt.BlurImage(src, dst1, 3, 3, MEDIAN);
	src = dst1;
	imshow("LAPLACE", dst1);
	imshow("source", src);
	src = dst1;
	/*EdgeDetector xx;
	xx.DetectEdge(src, dst1, 3, 3, SOBEL);
	xx.DetectEdge(src, dst2, 3, 3, PREWITT);
	xx.DetectEdge(src, dst3, 3, 3, LAPLACE);
	imshow("SOBEL", dst1);
	imshow("PREWITT", dst2);
	imshow("LAPLACE", dst3);
	imshow("source", src);*/

	waitKey(0);
	return 0;
}