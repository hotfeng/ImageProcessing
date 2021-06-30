#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main(int argc, char **argv)
{
    /** 加载原始图像并转为灰度图 **/
    cv::Mat srcImage, grayImage;

    srcImage = cv::imread("images/rectangle_noise.bmp", cv::IMREAD_COLOR);
    cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);


    /** 【高斯滤波】：将每一像素点的灰度值设置为该点某邻域窗口内的所有像素点灰度值的中值 **/
    cv::GaussianBlur(grayImage, grayImage, cv::Size(5, 5), 0, 0);

    /** 阈值分割（采用OTSU算法） **/
    cv::Mat threshImage;
    cv::threshold(grayImage, threshImage, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);


    /******* 方法二：形态学滤波：闭运算（先膨胀后腐蚀 ********/
    //自定义核
//    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
//
//    cv::Mat dstImage;
    //调用高级形态学变换函数进行闭运算（cv::MORPH_CLOSE：此参数表示采用闭运算进行图像处理）
//    cv::morphologyEx(threshImage, dstImage, cv::MORPH_CLOSE, element, cv::Point(-1, -1));


    /** 依靠方块轮廓计算面积 **/
    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    // 寻找方块轮廓
    cv::findContours(threshImage, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point());

    for (size_t i = 1; i < contours.size(); i++)
    {
         double area = cv::contourArea(contours[i]);
         cout << "第" << i << "个方块的面积 = " << area  << endl;
    }

    cv::imwrite("images/seg.jpg", threshImage);

    cv::namedWindow("【原始图】", cv::WINDOW_NORMAL);
    cv::namedWindow("【阈值分割】", cv::WINDOW_NORMAL);

    cv::imshow("【原始图】", srcImage);
    cv::imshow("【阈值分割】", threshImage);

    cv::waitKey(0);

	return 0;
}
