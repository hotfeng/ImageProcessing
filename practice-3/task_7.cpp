#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


void TwoPass(const cv::Mat& _binImg, cv::Mat& _lableImg);
cv::Scalar icvprGetRandomColor();
void LabelColor(const cv::Mat& _labelImg, cv::Mat& _colorLabelImg);


int main(int argc, char** argv)
{
	cv::Mat binImage = cv::imread("images/rectangles.bmp", 0) ;
	cv::threshold(binImage, binImage, 50, 1, cv::THRESH_BINARY_INV) ;

	// connected component labeling
	cv::Mat labelImg ;
	TwoPass(binImage, labelImg) ;
	//SeedFill(binImage, labelImg) ;

	// show result
	cv::Mat grayImg ;
	labelImg *= 10 ;
	labelImg.convertTo(grayImg, CV_8UC1) ;
	cv::imshow("labelImg", grayImg) ;

	cv::Mat colorLabelImg ;
	LabelColor(labelImg, colorLabelImg) ;
	cv::imshow("colorImg", colorLabelImg) ;
	cv::waitKey(0) ;

	return 0 ;
}


void TwoPass(const cv::Mat& _binImg, cv::Mat& _lableImg)
{
	// connected component analysis (4-component)
	// use two-pass algorithm
	// 1. first pass: label each foreground pixel with a label
	// 2. second pass: visit each labeled pixel and merge neighbor labels
	//
	// foreground pixel: _binImg(x,y) = 1
	// background pixel: _binImg(x,y) = 0


	if (_binImg.empty() ||
		_binImg.type() != CV_8UC1)
	{
		return ;
	}

	// 1. first pass

	_lableImg.release() ;
	_binImg.convertTo(_lableImg, CV_32SC1) ;

	int label = 1 ;  // start by 2
	std::vector<int> labelSet ;
	labelSet.push_back(0) ;   // background: 0
	labelSet.push_back(1) ;   // foreground: 1

	int rows = _binImg.rows - 1 ;
	int cols = _binImg.cols - 1 ;
	for (int i = 1; i < rows; i++)
	{
		int* data_preRow = _lableImg.ptr<int>(i-1) ;
		int* data_curRow = _lableImg.ptr<int>(i) ;
		for (int j = 1; j < cols; j++)
		{
			if (data_curRow[j] == 1)
			{
				std::vector<int> neighborLabels ;
				neighborLabels.reserve(2) ;
				int leftPixel = data_curRow[j-1] ;
				int upPixel = data_preRow[j] ;

				if ( leftPixel > 1)
				{
					neighborLabels.push_back(leftPixel) ;
				}
				if (upPixel > 1)
				{
					neighborLabels.push_back(upPixel) ;
				}

				if (neighborLabels.empty())
				{
					labelSet.push_back(++label) ;  // assign to a new label
					data_curRow[j] = label ;
					labelSet[label] = label ;
				}
				else
				{
					std::sort(neighborLabels.begin(), neighborLabels.end()) ;
					int smallestLabel = neighborLabels[0] ;
					data_curRow[j] = smallestLabel ;

					// save equivalence
					for (size_t k = 1; k < neighborLabels.size(); k++)
					{
						int tempLabel = neighborLabels[k] ;
						int& oldSmallestLabel = labelSet[tempLabel] ;

						if (oldSmallestLabel > smallestLabel)
						{
							labelSet[oldSmallestLabel] = smallestLabel ;
							oldSmallestLabel = smallestLabel ;
						}
						else if (oldSmallestLabel < smallestLabel)
						{
							labelSet[smallestLabel] = oldSmallestLabel ;
						}
					}
				}
			}
		}
	}

	// update equivalent labels
	// assigned with the smallest label in each equivalent label set
	for (size_t i = 2; i < labelSet.size(); i++)
	{
		int curLabel = labelSet[i] ;
		int preLabel = labelSet[curLabel] ;
		while (preLabel != curLabel)
		{
			curLabel = preLabel ;
			preLabel = labelSet[preLabel] ;
		}
		labelSet[i] = curLabel ;
	}


	// 2. second pass
	for (int i = 0; i < rows; i++)
	{
		int* data = _lableImg.ptr<int>(i) ;
		for (int j = 0; j < cols; j++)
		{
			int& pixelLabel = data[j] ;
			pixelLabel = labelSet[pixelLabel] ;
		}
	}
}


cv::Scalar GetRandomColor()
{
	uchar r = 255 * (rand()/(1.0 + RAND_MAX));
	uchar g = 255 * (rand()/(1.0 + RAND_MAX));
	uchar b = 255 * (rand()/(1.0 + RAND_MAX));
	return cv::Scalar(b,g,r) ;
}


void LabelColor(const cv::Mat& _labelImg, cv::Mat& _colorLabelImg)
{
	if (_labelImg.empty() ||
		_labelImg.type() != CV_32SC1)
	{
		return ;
	}

	std::map<int, cv::Scalar> colors ;

	int rows = _labelImg.rows ;
	int cols = _labelImg.cols ;

	_colorLabelImg.release() ;
	_colorLabelImg.create(rows, cols, CV_8UC3) ;
	_colorLabelImg = cv::Scalar::all(0) ;

	for (int i = 0; i < rows; i++)
	{
		const int* data_src = (int*)_labelImg.ptr<int>(i) ;
		uchar* data_dst = _colorLabelImg.ptr<uchar>(i) ;
		for (int j = 0; j < cols; j++)
		{
			int pixelValue = data_src[j] ;
			if (pixelValue > 1)
			{
				if (colors.count(pixelValue) <= 0)
				{
					colors[pixelValue] = GetRandomColor() ;
				}
				cv::Scalar color = colors[pixelValue] ;
				*data_dst++   = color[0] ;
				*data_dst++ = color[1] ;
				*data_dst++ = color[2] ;
			}
			else
			{
				data_dst++ ;
				data_dst++ ;
				data_dst++ ;
			}
		}
	}
}
