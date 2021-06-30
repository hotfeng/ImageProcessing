#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;

int main(void)
{
    // ��ȡԭͼ���ҶȻ�
    cv::Mat srcImage, grayImage;
    srcImage = cv::imread( "images/more_noise.jpg", cv::IMREAD_COLOR );
    cv::cvtColor( srcImage, grayImage, cv::COLOR_BGR2GRAY );

    // ��ȡ�ṹԪ�أ��ں˾���/ģ��/��Ĥ��
    cv::Mat kernel = cv::getStructuringElement( cv::MORPH_RECT, cv::Size(3, 3), cv::Point(-1, -1) );

    // ��̬ѧ��ʴ
    // ע�⣺��ʴ�����Ͷ������ͼ���еİ�ɫ�����������ֶ��Ե�
    // ������Ҫ����cv::erode�����еĵ����������ֵ����ʴ��������������
    cv::Mat dstImage;
    cv::erode( grayImage, dstImage, kernel, cv::Point(-1, -1), 3 );

    // ��ʾԭͼ/�Ҷ�ͼ/��ʴͼ
    cv::imshow( "[Source Image]", srcImage );
    cv::imshow( "[Gray Image]", grayImage );
    cv::imshow( "[Erode Image]", dstImage );

    cv::waitKey(0);

    return 0;
}
