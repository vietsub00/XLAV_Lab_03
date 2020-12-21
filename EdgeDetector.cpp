#include "EdgeDetector.h"

int EdgeDetector::DetectEdge(const Mat& sourceImage, Mat& destinationImage, int kWidth, int kHeight, int method)
{
    if (sourceImage.empty()) return 1;

	int kernelsize = kHeight * kWidth;
	vector<float> kernel;
	switch (method)
	{
	case SOBEL: {
		vector<float>kernel1 = { -1, -2, -1, 
								   0, 0, 0, 
								   1, 2, 1 };
		vector<float>kernel2 = { -1, 0, 1,
								 -2, 0, 2, 
								 -1, 0, 1 };
		Mat dst1, dst2;
		Convolution edtt1(kernel1, kWidth, kHeight);
		edtt1.DoConvolution(sourceImage, dst1);
		Convolution edtt2(kernel2, kWidth, kHeight);
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
		break;
	}
	case LAPLACE: {
		for (int i = 0; i < kernelsize; i++) {
			if (i - (kernelsize / 2) == 0) //Vị trí trung tâm của kernel
				kernel.push_back(kernelsize - 1);
			else kernel.push_back(-1);
		}
		break;
	}
	default:
		return 1;
		break;
	}

	Convolution edtt(kernel, kWidth, kHeight);
	edtt.DoConvolution(sourceImage, destinationImage);

    return 0;
}

EdgeDetector::EdgeDetector()
{
}

EdgeDetector::~EdgeDetector()
{
}
