#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


void find_moments(cv::Mat &grayImage, cv::Mat &dstImage);

int main()
{
	// 载入原图并转为灰度图
	cv::Mat srcImage, grayImage;
	srcImage = cv::imread("images/rectangle_2.bmp");

	cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);

	//显示原图
	cv::namedWindow("Source Image", cv::WINDOW_AUTOSIZE);
	cv::imshow("Source Image", srcImage);

	// 调用寻找质心的函数
	cv::Mat dstImage;
	find_moments(grayImage, dstImage);

	/** 显示质心检测结果 **/
	cv::namedWindow("Contours", cv::WINDOW_AUTOSIZE);
	cv::imshow("Contours", dstImage);

	cv::waitKey(0);

	return 0;
}

/** 寻找质心：arg1：待检测灰度图，arg2：包含质心的图（待输出） **/
void find_moments(cv::Mat &grayImage, cv::Mat &dstImage)
{
	cv::Mat edges;
	//各个轮廓的点集合
	vector<vector<cv::Point> > contours;
	//轮廓输出结果向量
	vector<cv::Vec4i> hierarchy;

	/** Canny边缘检测 **/
	cv::Canny(grayImage, edges, 50, 150, 3);
	// 寻找边缘图中轮廓，RETR_TREE表示提取所有轮廓
	cv::findContours(edges, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	/** Get the moments 图像矩 **/
	vector<cv::Moments> momts(contours.size());
	//求取每个轮廓的矩
	for (int i = 0; i < contours.size(); i++)
	{
		momts[i] = cv::moments(contours[i], false);
	}

	/**  Get the centroid of figures. 轮廓质点 **/
	vector<cv::Point2f> centroids(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		centroids[i] = cv::Point2f(momts[i].m10 / momts[i].m00, momts[i].m01 / momts[i].m00);
	}

	/** 画轮廓 **/
	dstImage = cv::Mat(edges.size(), CV_8UC3, cv::Scalar(255, 255, 255));

	for (int i = 0; i < contours.size(); i++)
	{
		cv::Scalar color = cv::Scalar(0, 0, 255);
		//画轮廓
		cv::drawContours(dstImage, contours, i, color, 2, 8, hierarchy, 0, cv::Point());
		//画质心
		cv::circle(dstImage, centroids[i], 4, color, -1, 7, 0);
	}

}
