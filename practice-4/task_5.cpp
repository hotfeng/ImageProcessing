#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace std;

/** 声明全局变量：原图像，效果图， 滤波参数**/
cv::Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3;
int g_nBoxFilterVal = 3;        //方框滤波核参数
int g_nMeanFilterVal = 3;       //均值滤波核参数
int g_nGaussianFilterVal = 3;   //高斯滤波核参数

/** 声明回调函数，配合滑动条动态调节滤波参数值 **/
static void on_BoxFilter(int, void *);      //方框滤波
static void on_MeanBlur(int, void *);       //均值滤波
static void on_GaussianBlur(int, void *);   //高斯滤波

int main(int argc, char **argv)
{
    // 载入原图并显示
    g_srcImage = cv::imread("images/lenargb.bmp", cv::IMREAD_COLOR);
    if (g_srcImage.empty())
    {
        cout << "\nCan not open image file!" << endl;
        return false;
    }
    cv::namedWindow("[1]原图", cv::WINDOW_AUTOSIZE);
    cv::imshow("[1]原图", g_srcImage);


    /** 将原图复制到三幅效果图中 **/
    g_dstImage1 = g_srcImage.clone();
    g_dstImage2 = g_srcImage.clone();
    g_dstImage3 = g_srcImage.clone();


    /** 方框滤波 **/
    cv::namedWindow("[2]方框滤波", cv::WINDOW_AUTOSIZE);    // 打开显示窗口
    cv::createTrackbar("内核值：", "[2]方框滤波", &g_nBoxFilterVal, 40, on_BoxFilter);  // 创建滑动条
    on_BoxFilter(g_nBoxFilterVal, 0);       // 调用回调函数以响应内核值

    /** 均值滤波 **/
    cv::namedWindow("[3]均值滤波", cv::WINDOW_AUTOSIZE);    // 打开显示窗口
    cv::createTrackbar("内核值：", "[3]均值滤波", &g_nMeanFilterVal, 40, on_MeanBlur);  // 创建滑动条
    on_BoxFilter(g_nMeanFilterVal, 0);      // 调用回调函数以响应内核值

    /** 高斯滤波 **/
    cv::namedWindow("[4]高斯滤波", cv::WINDOW_AUTOSIZE);    // 打开显示窗口
    cv::createTrackbar("内核值：", "[4]高斯滤波", &g_nGaussianFilterVal, 40, on_GaussianBlur);  // 创建滑动条
    on_BoxFilter(g_nGaussianFilterVal, 0);   // 调用回调函数以响应内核值


    // Help Messages.
    cout << "滚动滑动条以改变滤波效果!\n" << "按'q'退出!" << endl;
    while (cv::waitKey(0)=='q')
    {
        break;
    }
	return 0;
}

/** 方框滤波的回调函数 **/
static void on_BoxFilter(int, void *)
{
    // 调用方框滤波函数进行图像滤波处理
    cv::boxFilter(g_srcImage, g_dstImage1, -1, cv::Size(g_nBoxFilterVal + 1, g_nBoxFilterVal + 1), cv::Point(-1, -1));
    // 显示方框滤波效果图
    cv::imshow("[2]方框滤波", g_dstImage1);
}

/** 均值滤波的回调函数 **/
static void on_MeanBlur(int, void *)
{
    // 调用均值波函数进行图像滤波处理
    cv::blur(g_srcImage, g_dstImage2, cv::Size(g_nMeanFilterVal + 1, g_nMeanFilterVal + 1), cv::Point(-1, -1));
    // 显示均值滤波效果图
    cv::imshow("[3]均值滤波", g_dstImage2);
}

/** 高斯滤波的回调函数 **/
static void on_GaussianBlur(int, void *)
{
    // 调用高斯波函数进行图像滤波处理
    cv::GaussianBlur(g_srcImage, g_dstImage3, cv::Size(g_nGaussianFilterVal*2 + 1, g_nGaussianFilterVal*2 + 1), 0, 0);
    // 显示高斯滤波效果图
    cv::imshow("[4]高斯滤波", g_dstImage3);
}
