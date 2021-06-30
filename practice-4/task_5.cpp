#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace std;

/** ����ȫ�ֱ�����ԭͼ��Ч��ͼ�� �˲�����**/
cv::Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3;
int g_nBoxFilterVal = 3;        //�����˲��˲���
int g_nMeanFilterVal = 3;       //��ֵ�˲��˲���
int g_nGaussianFilterVal = 3;   //��˹�˲��˲���

/** �����ص���������ϻ�������̬�����˲�����ֵ **/
static void on_BoxFilter(int, void *);      //�����˲�
static void on_MeanBlur(int, void *);       //��ֵ�˲�
static void on_GaussianBlur(int, void *);   //��˹�˲�

int main(int argc, char **argv)
{
    // ����ԭͼ����ʾ
    g_srcImage = cv::imread("images/lenargb.bmp", cv::IMREAD_COLOR);
    if (g_srcImage.empty())
    {
        cout << "\nCan not open image file!" << endl;
        return false;
    }
    cv::namedWindow("[1]ԭͼ", cv::WINDOW_AUTOSIZE);
    cv::imshow("[1]ԭͼ", g_srcImage);


    /** ��ԭͼ���Ƶ�����Ч��ͼ�� **/
    g_dstImage1 = g_srcImage.clone();
    g_dstImage2 = g_srcImage.clone();
    g_dstImage3 = g_srcImage.clone();


    /** �����˲� **/
    cv::namedWindow("[2]�����˲�", cv::WINDOW_AUTOSIZE);    // ����ʾ����
    cv::createTrackbar("�ں�ֵ��", "[2]�����˲�", &g_nBoxFilterVal, 40, on_BoxFilter);  // ����������
    on_BoxFilter(g_nBoxFilterVal, 0);       // ���ûص���������Ӧ�ں�ֵ

    /** ��ֵ�˲� **/
    cv::namedWindow("[3]��ֵ�˲�", cv::WINDOW_AUTOSIZE);    // ����ʾ����
    cv::createTrackbar("�ں�ֵ��", "[3]��ֵ�˲�", &g_nMeanFilterVal, 40, on_MeanBlur);  // ����������
    on_BoxFilter(g_nMeanFilterVal, 0);      // ���ûص���������Ӧ�ں�ֵ

    /** ��˹�˲� **/
    cv::namedWindow("[4]��˹�˲�", cv::WINDOW_AUTOSIZE);    // ����ʾ����
    cv::createTrackbar("�ں�ֵ��", "[4]��˹�˲�", &g_nGaussianFilterVal, 40, on_GaussianBlur);  // ����������
    on_BoxFilter(g_nGaussianFilterVal, 0);   // ���ûص���������Ӧ�ں�ֵ


    // Help Messages.
    cout << "�����������Ըı��˲�Ч��!\n" << "��'q'�˳�!" << endl;
    while (cv::waitKey(0)=='q')
    {
        break;
    }
	return 0;
}

/** �����˲��Ļص����� **/
static void on_BoxFilter(int, void *)
{
    // ���÷����˲���������ͼ���˲�����
    cv::boxFilter(g_srcImage, g_dstImage1, -1, cv::Size(g_nBoxFilterVal + 1, g_nBoxFilterVal + 1), cv::Point(-1, -1));
    // ��ʾ�����˲�Ч��ͼ
    cv::imshow("[2]�����˲�", g_dstImage1);
}

/** ��ֵ�˲��Ļص����� **/
static void on_MeanBlur(int, void *)
{
    // ���þ�ֵ����������ͼ���˲�����
    cv::blur(g_srcImage, g_dstImage2, cv::Size(g_nMeanFilterVal + 1, g_nMeanFilterVal + 1), cv::Point(-1, -1));
    // ��ʾ��ֵ�˲�Ч��ͼ
    cv::imshow("[3]��ֵ�˲�", g_dstImage2);
}

/** ��˹�˲��Ļص����� **/
static void on_GaussianBlur(int, void *)
{
    // ���ø�˹����������ͼ���˲�����
    cv::GaussianBlur(g_srcImage, g_dstImage3, cv::Size(g_nGaussianFilterVal*2 + 1, g_nGaussianFilterVal*2 + 1), 0, 0);
    // ��ʾ��˹�˲�Ч��ͼ
    cv::imshow("[4]��˹�˲�", g_dstImage3);
}
