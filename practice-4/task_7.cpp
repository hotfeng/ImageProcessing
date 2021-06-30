#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
    // 读入原图并灰度化
    cv::Mat srcImage, grayImage;
    srcImage = cv::imread("images/noise.jpg", cv::IMREAD_COLOR);
    cv::imshow("噪声原图", srcImage);

    cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);
    cv::imshow("噪声灰度图", grayImage);

    // 高斯滤波
    cv::GaussianBlur(grayImage, grayImage, cv::Size(5, 5), 0, 0);
    cv::imshow("噪声-高斯滤波", grayImage);

    // 阈值分割
    cv::Mat threholdImage;
    cv::threshold(grayImage, threholdImage, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::imshow("噪声-阈值分割", threholdImage);

    // 图像形态学-腐蚀
    cv::Mat dstImage;
    cv::Point anchor = cv::Point(-1, -1);
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), anchor);

    cv::morphologyEx(threholdImage, dstImage, cv::MORPH_ERODE, element, anchor);
    cv::imshow("噪声-形态学腐蚀", dstImage);

    /** 依靠方块轮廓计算面积 **/
    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    // 寻找方块轮廓
    cv::findContours(dstImage, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point());
    //sort(contours.begin(), contours.end());

    for (size_t i = 1; i < contours.size(); i++)
    {
         double area = cv::contourArea(contours[i]);
         cout << "第" << i << "个方块的面积 = " << area  << endl;
    }

    cv::waitKey(0);

	return 0;
}
