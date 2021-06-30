#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;

int main(void)
{
    // 读取原图并灰度化
    cv::Mat srcImage, grayImage;
    srcImage = cv::imread( "images/less_noise.jpg", cv::IMREAD_COLOR );
    cv::cvtColor( srcImage, grayImage, cv::COLOR_BGR2GRAY );

    // 获取结构元素（内核矩阵/模板/掩膜）
    cv::Mat kernel = cv::getStructuringElement( cv::MORPH_RECT, cv::Size(3, 3), cv::Point(-1, -1) );

    // 形态学膨胀
    // 根据需要增加cv::dilate函数中的第五个参数的值（膨胀操作迭代次数）
    cv::Mat dstImage;
    cv::dilate( grayImage, dstImage, kernel, cv::Point(-1, -1), 5 );

    // 显示原图/灰度图/膨胀图
    cv::imshow( "[Source Image]", srcImage );
    cv::imshow( "[Gray Image]", grayImage );
    cv::imshow( "[Dilate Image]", dstImage );

    cv::waitKey(0);

    return 0;
}
