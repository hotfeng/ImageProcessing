#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
    // ����ԭͼ���ҶȻ�
    cv::Mat srcImage, grayImage;
    srcImage = cv::imread("images/noise.jpg", cv::IMREAD_COLOR);
    cv::imshow("����ԭͼ", srcImage);

    cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);
    cv::imshow("�����Ҷ�ͼ", grayImage);

    // ��˹�˲�
    cv::GaussianBlur(grayImage, grayImage, cv::Size(5, 5), 0, 0);
    cv::imshow("����-��˹�˲�", grayImage);

    // ��ֵ�ָ�
    cv::Mat threholdImage;
    cv::threshold(grayImage, threholdImage, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::imshow("����-��ֵ�ָ�", threholdImage);

    // ͼ����̬ѧ-��ʴ
    cv::Mat dstImage;
    cv::Point anchor = cv::Point(-1, -1);
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), anchor);

    cv::morphologyEx(threholdImage, dstImage, cv::MORPH_ERODE, element, anchor);
    cv::imshow("����-��̬ѧ��ʴ", dstImage);

    /** ������������������� **/
    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    // Ѱ�ҷ�������
    cv::findContours(dstImage, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point());
    //sort(contours.begin(), contours.end());

    for (size_t i = 1; i < contours.size(); i++)
    {
         double area = cv::contourArea(contours[i]);
         cout << "��" << i << "���������� = " << area  << endl;
    }

    cv::waitKey(0);

	return 0;
}
