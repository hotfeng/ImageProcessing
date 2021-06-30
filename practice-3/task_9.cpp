#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main(int argc, char **argv)
{
    /** ����ԭʼͼ��תΪ�Ҷ�ͼ **/
    cv::Mat srcImage, grayImage;

    srcImage = cv::imread("images/rectangle_noise.bmp", cv::IMREAD_COLOR);
    cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);


    /** ����˹�˲�������ÿһ���ص�ĻҶ�ֵ����Ϊ�õ�ĳ���򴰿��ڵ��������ص�Ҷ�ֵ����ֵ **/
    cv::GaussianBlur(grayImage, grayImage, cv::Size(5, 5), 0, 0);

    /** ��ֵ�ָ����OTSU�㷨�� **/
    cv::Mat threshImage;
    cv::threshold(grayImage, threshImage, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);


    /******* ����������̬ѧ�˲��������㣨�����ͺ�ʴ ********/
    //�Զ����
//    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
//
//    cv::Mat dstImage;
    //���ø߼���̬ѧ�任�������б����㣨cv::MORPH_CLOSE���˲�����ʾ���ñ��������ͼ����
//    cv::morphologyEx(threshImage, dstImage, cv::MORPH_CLOSE, element, cv::Point(-1, -1));


    /** ������������������� **/
    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    // Ѱ�ҷ�������
    cv::findContours(threshImage, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point());

    for (size_t i = 1; i < contours.size(); i++)
    {
         double area = cv::contourArea(contours[i]);
         cout << "��" << i << "���������� = " << area  << endl;
    }

    cv::imwrite("images/seg.jpg", threshImage);

    cv::namedWindow("��ԭʼͼ��", cv::WINDOW_NORMAL);
    cv::namedWindow("����ֵ�ָ", cv::WINDOW_NORMAL);

    cv::imshow("��ԭʼͼ��", srcImage);
    cv::imshow("����ֵ�ָ", threshImage);

    cv::waitKey(0);

	return 0;
}
