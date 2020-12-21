#include "EdgeDetector.h"

int EdgeDetector::DetectEdge(const Mat& sourceImage, Mat& destinationImage, int kWidth, int kHeight, int method)
{
	if (sourceImage.empty()) return 1;

	int kernelsize = kHeight * kWidth;
	vector<float> kernel;
	switch (method)
	{
	case SOBEL: {

		Mat dst1, dst2;
		
		int x = kHeight / 2;
		for (int i = 0; i < kHeight; i++)
		{
			for (int j = 0; j < kWidth; j++)
			{
				if (j != kWidth / 2)
					kernel.push_back(x);
				else
					kernel.push_back(x*2);
			}
			x--;
		} 
		Convolution edtt1(kernel, kWidth, kHeight);
		
		kernel.resize(0);
		
		for (int i = 0; i < kHeight; i++)
		{
			for (int j = -kWidth/2; j <= kWidth/2; j++)
			{
				if (i != kHeight / 2)
					kernel.push_back(j);
				else
					kernel.push_back(j*2);
			}
		}
		Convolution edtt2(kernel, kWidth, kHeight);
		
		edtt1.DoConvolution(sourceImage, dst1);
		edtt2.DoConvolution(sourceImage, dst2);

		destinationImage = Mat(sourceImage.rows, sourceImage.cols, CV_8UC1);
		uint8_t* pDstData1 = (uint8_t*)dst1.data;
		uint8_t* pDstData2 = (uint8_t*)dst2.data;
		uint8_t* pDstData = (uint8_t*)destinationImage.data;

		for (int i = 0; i < sourceImage.rows; i++) {
			for (int j = 0; j < sourceImage.cols; j++) {
				int index = i * sourceImage.cols + j;
				pDstData[index] = (pDstData1[index] + pDstData2[index]) / 2;
			}
		}

		return 0;
	}
	case PREWITT: {
		Mat dst1, dst2;

		int x = kHeight / 2;
		for (int i = 0; i < kHeight; i++)
		{
			for (int j = 0; j < kWidth; j++)
			{
				kernel.push_back(x);
			}
			x--;
		}
		Convolution edtt1(kernel, kWidth, kHeight);

		kernel.resize(0);

		for (int i = 0; i < kHeight; i++)
		{
			for (int j = -kWidth / 2; j <= kWidth / 2; j++)
			{
				kernel.push_back(j);
			}
		}
		Convolution edtt2(kernel, kWidth, kHeight);

		edtt1.DoConvolution(sourceImage, dst1);
		edtt2.DoConvolution(sourceImage, dst2);

		destinationImage = Mat(sourceImage.rows, sourceImage.cols, CV_8UC1);
		uint8_t* pDstData1 = (uint8_t*)dst1.data;
		uint8_t* pDstData2 = (uint8_t*)dst2.data;
		uint8_t* pDstData = (uint8_t*)destinationImage.data;

		for (int i = 0; i < sourceImage.rows; i++) {
			for (int j = 0; j < sourceImage.cols; j++) {
				int index = i * sourceImage.cols + j;
				pDstData[index] = (pDstData1[index] + pDstData2[index]) / 2;
			}
		}

		return 0;
	}
	case LAPLACE: {
		for (int i = 0; i < kernelsize; i++) {
			if (i - (kernelsize / 2) == 0) //Vị trí trung tâm của kernel
				kernel.push_back(kernelsize - 1);
			else kernel.push_back(-1);
		}

		Convolution edtt(kernel, kWidth, kHeight);
		edtt.DoConvolution(sourceImage, destinationImage);

		break;
	}
	default:
		return 1;
		break;
	}

	/*Convolution edtt(kernel, kWidth, kHeight);
	edtt.DoConvolution(sourceImage, destinationImage);*/

	return 0;
}

EdgeDetector::EdgeDetector()
{
}

EdgeDetector::~EdgeDetector()
{
}
