#include "Blur.h"

int Blur::BlurImage(const Mat& sourceImage, Mat& destinationImage, int kWidth, int kHeight, int method)
{
	if (sourceImage.empty()) return 1;

	int kernelSize = kWidth * kHeight;
	vector<float> kernel;
	switch (method) {
	case MEAN: { //Mean
		for (int i = 0; i < kernelSize; i++) {
			kernel.push_back(1);
		}
		break;
	}
	case MEDIAN: { //Median (không dùng được convolution)
		int nrow = sourceImage.rows;
		int ncol = sourceImage.cols;
		int nChannels = sourceImage.channels();
		int kernelSize = kHeight * kWidth;

		vector<uchar> medianKernel(kernelSize);

		if (sourceImage.channels() == 1)
			destinationImage = Mat(nrow, ncol, CV_8UC1);
		else
			destinationImage = Mat(nrow, ncol, CV_8UC3);

		uint8_t* pSrcData = (uint8_t*)sourceImage.data;
		uint8_t* pDstData = (uint8_t*)destinationImage.data;

		for (int cn = 0; cn < nChannels; cn++) {
			for (int i = 0; i < nrow; i++) {
				for (int j = 0; j < ncol; j++) {
					int index = i * ncol * nChannels + j * nChannels + cn;
					for (int k = 0; k < kernelSize; k++) {
						int row = (k / kWidth) - (kHeight / 2);
						int col = (k % kWidth) - (kWidth / 2);
						//Xử lý kernel của pixel ở cạnh bằng cách lấy đối xứng qua pixel đó
						if (i + row < 0 || i + row >= nrow) row = -row;
						if (j + col < 0 || j + col >= ncol) col = -col;

						medianKernel[k] = pSrcData[index + row * ncol * nChannels + col * nChannels];
					}
					//xắp sếp các phần tử trong kernel 
					sort(medianKernel.begin(), medianKernel.end());
					//lấy phần tử median ở chính giữa
					pDstData[index] = medianKernel[kernelSize / 2];
				}
			}
		}
		return 0;
	}
	case GAUSSIAN: { //Gaussian
		float sigma = 1.0;
		float r, s = 2.0 * sigma * sigma;
		float sum = 0.0;

		for (int x = -kHeight / 2; x <= kHeight / 2; x++)
		{
			for (int y = -kWidth / 2; y <= kWidth / 2; y++)
			{
				r = sqrt(x * x + y * y);
				float temp = (exp(-(r * r) / s)) / (PI * s);
				kernel.push_back(temp);
				sum += temp;
			}
		}
		for (int i = 0; i < kernelSize; i++)
			kernel[i] /= sum;
		break;
	}
	default:
		return 1;
	}

	Convolution blur(kernel, kWidth, kHeight);
	blur.DoConvolution(sourceImage, destinationImage);

	return 0;
}

Blur::Blur()
{

}

Blur::~Blur()
{
}

bool comp(int i, int j)
{
	return (i > j);
}
