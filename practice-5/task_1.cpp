#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;

int main(void)
{
    // 读取原图并灰度化
    cv::Mat srcImage, grayImage;
    srcImage = cv::imread( "images/more_noise.jpg", cv::IMREAD_COLOR );
    cv::cvtColor( srcImage, grayImage, cv::COLOR_BGR2GRAY );

    // 获取结构元素（内核矩阵/模板/掩膜）
    cv::Mat kernel = cv::getStructuringElement( cv::MORPH_RECT, cv::Size(3, 3), cv::Point(-1, -1) );

    // 形态学腐蚀
    // 注意：腐蚀及膨胀都是针对图像中的白色（高亮）部分而言的
    // 根据需要增加cv::erode函数中的第五个参数的值（腐蚀操作迭代次数）
    cv::Mat dstImage;
    cv::erode( grayImage, dstImage, kernel, cv::Point(-1, -1), 3 );

    // 显示原图/灰度图/腐蚀图
    cv::imshow( "[Source Image]", srcImage );
    cv::imshow( "[Gray Image]", grayImage );
    cv::imshow( "[Erode Image]", dstImage );

    cv::waitKey(0);

    return 0;
}
