#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


void find_moments(cv::Mat &grayImage, cv::Mat &dstImage);

int main()
{
	// ����ԭͼ��תΪ�Ҷ�ͼ
	cv::Mat srcImage, grayImage;
	srcImage = cv::imread("images/rectangle_2.bmp");

	cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);

	//��ʾԭͼ
	cv::namedWindow("Source Image", cv::WINDOW_AUTOSIZE);
	cv::imshow("Source Image", srcImage);

	// ����Ѱ�����ĵĺ���
	cv::Mat dstImage;
	find_moments(grayImage, dstImage);

	/** ��ʾ���ļ���� **/
	cv::namedWindow("Contours", cv::WINDOW_AUTOSIZE);
	cv::imshow("Contours", dstImage);

	cv::waitKey(0);

	return 0;
}

/** Ѱ�����ģ�arg1�������Ҷ�ͼ��arg2���������ĵ�ͼ��������� **/
void find_moments(cv::Mat &grayImage, cv::Mat &dstImage)
{
	cv::Mat edges;
	//���������ĵ㼯��
	vector<vector<cv::Point> > contours;
	//��������������
	vector<cv::Vec4i> hierarchy;

	/** Canny��Ե��� **/
	cv::Canny(grayImage, edges, 50, 150, 3);
	// Ѱ�ұ�Եͼ��������RETR_TREE��ʾ��ȡ��������
	cv::findContours(edges, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	/** Get the moments ͼ��� **/
	vector<cv::Moments> momts(contours.size());
	//��ȡÿ�������ľ�
	for (int i = 0; i < contours.size(); i++)
	{
		momts[i] = cv::moments(contours[i], false);
	}

	/**  Get the centroid of figures. �����ʵ� **/
	vector<cv::Point2f> centroids(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		centroids[i] = cv::Point2f(momts[i].m10 / momts[i].m00, momts[i].m01 / momts[i].m00);
	}

	/** ������ **/
	dstImage = cv::Mat(edges.size(), CV_8UC3, cv::Scalar(255, 255, 255));

	for (int i = 0; i < contours.size(); i++)
	{
		cv::Scalar color = cv::Scalar(0, 0, 255);
		//������
		cv::drawContours(dstImage, contours, i, color, 2, 8, hierarchy, 0, cv::Point());
		//������
		cv::circle(dstImage, centroids[i], 4, color, -1, 7, 0);
	}

}
