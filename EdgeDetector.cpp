#include "EdgeDetector.h"

int EdgeDetector::DetectEdge(const Mat& sourceImage, Mat& destinationImage, int kWidth, int kHeight, int method)
{
	if (sourceImage.empty()) return 1;

	int kernelsize = kHeight * kWidth;
	vector<float> kernel;
	switch (method){
	case SOBEL: {
		Mat dst1, dst2;
		//tạo kernel cho dst1
		for (int i = -kHeight/2; i <= kHeight/2; i++){
			for (int j = 0; j < kWidth; j++){
				if (j != kWidth / 2)
					kernel.push_back(-i);
				else
					kernel.push_back(-i * 2);	//nếu j ở ngay giữa kernel (tương ứng với cột ở giữa) thì vị trí đó được nhân 2
			}
		}
		Convolution edtt1(kernel, kWidth, kHeight);	//tạo biến cho dst1 có kernel vừa tạo

		kernel.resize(0);	//cho kích thước kernel cục bộ trở về 0
		//tạo kernel cho dst2
		for (int i = 0; i < kHeight; i++){
			for (int j = -kWidth / 2; j <= kWidth / 2; j++){
				if (i != kHeight / 2)
					kernel.push_back(-j);
				else
					kernel.push_back(-j * 2);	//nếu i ở ngay giữa kernel (tương ứng với hàng ở giữa) thì vị trí đó được nhân 2
			}
		}
		Convolution edtt2(kernel, kWidth, kHeight);	//tạo biến cho dst2 có kernel vừa tạo

		edtt1.DoConvolution(sourceImage, dst1);
		edtt2.DoConvolution(sourceImage, dst2);
		
		//Sau khi tìm được ảnh 1 (dst1) và ảnh 2 (dst2), ta lấy giá trị trung bình ở vị trí điểm ảnh tương ứng
		//ở hai hình rồi gán cho ảnh mới ở vị trí điểm ảnh tương ứng
		destinationImage = Mat(sourceImage.rows, sourceImage.cols, sourceImage.type());
		uint8_t* pDstData1 = (uint8_t*)dst1.data;
		uint8_t* pDstData2 = (uint8_t*)dst2.data;
		uint8_t* pDstData = (uint8_t*)destinationImage.data;

		for (int cn = 0; cn < sourceImage.channels(); cn++){
			for (int i = 0; i < sourceImage.rows; i++) {
				for (int j = 0; j < sourceImage.cols; j++){
					int index = i * sourceImage.cols * sourceImage.channels() + j * sourceImage.channels() + cn;
					pDstData[index] = (pDstData1[index] + pDstData2[index]) / 2;
				}
			}
		}

		return 0;
	}
	case PREWITT: {
		Mat dst1, dst2;
		
		//tạo kernel cho ảnh dst1
		for (int i = -kHeight / 2; i <= kHeight / 2; i++){
			for (int j = 0; j < kWidth; j++){
				kernel.push_back(-i);
			}
		}
		Convolution edtt1(kernel, kWidth, kHeight);	//tạo biến cho dst1 có kernel vừa tạo

		kernel.resize(0);	//cho kernel cục bộ về kích thước 0
		
		//tạo kernel cho ảnh dst2
		for (int i = 0; i < kHeight; i++){
			for (int j = -kWidth / 2; j <= kWidth / 2; j++){
				kernel.push_back(-j);
			}
		}
		Convolution edtt2(kernel, kWidth, kHeight);	//tạo biến cho dst2 có kernel vừa tạo

		edtt1.DoConvolution(sourceImage, dst1);
		edtt2.DoConvolution(sourceImage, dst2);
		
		//Sau khi tìm được ảnh 1 (dst1) và ảnh 2 (dst2), ta lấy giá trị trung bình ở vị trí điểm ảnh tương ứng
		//ở hai hình rồi gán cho ảnh mới ở vị trí điểm ảnh tương ứng
		destinationImage = Mat(sourceImage.rows, sourceImage.cols, sourceImage.type());
		uint8_t* pDstData1 = (uint8_t*)dst1.data;
		uint8_t* pDstData2 = (uint8_t*)dst2.data;
		uint8_t* pDstData = (uint8_t*)destinationImage.data;

		for (int cn = 0; cn < sourceImage.channels(); cn++){
			for (int i = 0; i < sourceImage.rows; i++) {
				for (int j = 0; j < sourceImage.cols; j++){
					int index = i * sourceImage.cols * sourceImage.channels() + j * sourceImage.channels() + cn;
					pDstData[index] = (pDstData1[index] + pDstData2[index]) / 2;
				}
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
