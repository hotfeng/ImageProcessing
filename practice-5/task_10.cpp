#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;

int main(int argc, char** argv)
{
    // 读入原图
    cv::Mat lenaImg = cv::imread( "images/lena.jpg", cv::IMREAD_COLOR );
    cv::Mat logoImg = cv::imread( "images/logo.jpg", cv::IMREAD_COLOR );

    // 使logoImg与lenaImg的尺寸一样
    cv::resize(logoImg, logoImg, lenaImg.size() );

    // 图像相加
    cv::Mat dstImg_1;
    cv::add( lenaImg, logoImg, dstImg_1 );
    cv::imshow( "[cv::add()]", dstImg_1 );

    // 图像混合
    cv::Mat dstImg_2;
    cv::addWeighted( lenaImg, 0.8, logoImg, 0.4, 0, dstImg_2 );
    cv::imshow( "cv::addWeighted()",dstImg_2 );

    // 图像按位操作
    cv::Mat dstImg_3;

    // 调整logo图像尺寸
    cv::resize( logoImg, logoImg, cv::Size(), 0.2, 0.2 );

    // 定义感兴趣区域
    cv::Mat ROI = lenaImg( cv::Rect(50, 50, logoImg.cols, logoImg.rows) );

    cv::Mat gray;
    cv::cvtColor( logoImg, gray, cv::COLOR_BGR2GRAY );

    // 将掩膜复制到ROI处
    logoImg.copyTo( ROI, gray );
    cv::imshow( "cv::copyTo()", lenaImg );

    cv::waitKey(0);

    return 0;
}
