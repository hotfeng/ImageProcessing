#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;

int main(int argc, char** argv)
{
    // ����ԭͼ
    cv::Mat lenaImg = cv::imread( "images/lena.jpg", cv::IMREAD_COLOR );
    cv::Mat logoImg = cv::imread( "images/logo.jpg", cv::IMREAD_COLOR );

    // ʹlogoImg��lenaImg�ĳߴ�һ��
    cv::resize(logoImg, logoImg, lenaImg.size() );

    // ͼ�����
    cv::Mat dstImg_1;
    cv::add( lenaImg, logoImg, dstImg_1 );
    cv::imshow( "[cv::add()]", dstImg_1 );

    // ͼ����
    cv::Mat dstImg_2;
    cv::addWeighted( lenaImg, 0.8, logoImg, 0.4, 0, dstImg_2 );
    cv::imshow( "cv::addWeighted()",dstImg_2 );

    // ͼ��λ����
    cv::Mat dstImg_3;

    // ����logoͼ��ߴ�
    cv::resize( logoImg, logoImg, cv::Size(), 0.2, 0.2 );

    // �������Ȥ����
    cv::Mat ROI = lenaImg( cv::Rect(50, 50, logoImg.cols, logoImg.rows) );

    cv::Mat gray;
    cv::cvtColor( logoImg, gray, cv::COLOR_BGR2GRAY );

    // ����Ĥ���Ƶ�ROI��
    logoImg.copyTo( ROI, gray );
    cv::imshow( "cv::copyTo()", lenaImg );

    cv::waitKey(0);

    return 0;
}
