#include "Convolution.h"

vector<float> Convolution::GetKernel()
{
    return this->_kernel;
}

void Convolution::SetKernel(vector<float> kernel, int kWidth, int kHeight)
{
    this->_kernel = kernel;
    this->_kernelWidth = kWidth;
    this->_kernelHeight = kHeight;
}

int Convolution::DoConvolution(const Mat& sourceImage, Mat& destinationImage)
{
    if (sourceImage.empty()) return 1;

    int nrow = sourceImage.rows;
    int ncol = sourceImage.cols;
    int nChannels = sourceImage.channels();
    int _kernelSize = _kernelHeight * _kernelWidth;
    
    destinationImage = Mat(nrow, ncol, sourceImage.type());

    uint8_t* pSrcData = (uint8_t*)sourceImage.data;
    uint8_t* pDstData = (uint8_t*)destinationImage.data;

    int kernelsum = 0; //kernelsum: tổng giá trị các phần tử trong kernel.
    for (int i = 0; i < _kernelSize; i++) kernelsum += _kernel[i];
    if (kernelsum == 0) kernelsum = 1;
    
    //Duyệt qua các pixel trong ảnh đích
    for (int cn = 0; cn < nChannels; cn++) {
        for (int i = 0; i < nrow; i++) {
            for (int j = 0; j < ncol; j++) {
                int index = i * ncol * nChannels + j * nChannels + cn;
                //sum: kết quả của phép tính tích chập
                int sum = 0;
                //duyệt qua các pixel trong ảnh nguồn tương ứng với vị trí trong kernel 
                for (int k = 0; k < _kernelSize; k++) {
                    int row = (k / _kernelWidth) - (_kernelHeight / 2);
                    int col = (k % _kernelWidth) - (_kernelWidth / 2);
                    //Xử lý kernel của pixel ở cạnh bằng cách lấy đối xứng qua pixel đó
                    if (i + row < 0 || i + row >= nrow) row = -row;
                    if (j + col < 0 || j + col >= ncol) col = -col;

                    sum += _kernel[k] * pSrcData[index + row * ncol * nChannels + col * nChannels];
                }
                if (kernelsum == 0) kernelsum = 1;
                pDstData[index] = fabs((float)sum / (float)kernelsum);
            }
        }
    }
    return 0;
}

Convolution::Convolution()
{
    this->_kernelHeight = 0;
    this->_kernelWidth = 0;
    this->_kernel = {};
}

Convolution::Convolution(vector<float> kernel, int kWidth, int kHeight)
{
    this->_kernel = kernel;
    this->_kernelWidth = kWidth;
    this->_kernelHeight = kHeight;
}

Convolution::~Convolution()
{
}
