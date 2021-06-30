#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main(void)
{
    cv::Mat srcImg = cv::imread("images/1.jpg", 1);
    cv::resize(srcImg, srcImg, cv::Size(), 0.5, 0.5);

    cv::Mat grayImg;
    cv::cvtColor(srcImg, grayImg, cv::COLOR_BGR2GRAY);

    cv::blur(grayImg, grayImg, cv::Size(5, 5));

    cv::Mat binaryImg;
    cv::threshold(grayImg, binaryImg, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    cv::imshow("1", grayImg);
    cv::imshow("2", binaryImg);
    cv::waitKey(0);

	return 0;
}
