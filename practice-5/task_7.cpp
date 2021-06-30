#include <iostream>
#include <cmath>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;

double getDistance( cv::Point pointO, cv::Point point1 );

int main(void)
{
    /** 读取原图并灰度化 **/
    cv::Mat srcImage, grayImage;
    srcImage = cv::imread( "images/center_detection.jpg", cv::IMREAD_COLOR );
    cv::cvtColor( srcImage, grayImage, cv::COLOR_BGR2GRAY );
    // 显示原图
    cv::imshow( "[Source Image]", srcImage );
    // cv::bitwise_not( grayImage, grayImage );     // 按位取反

    // /** 高斯滤波 **/
    // GaussianBlur( grayImage, grayImage, cv::Size(9, 9), 2, 2 );
    // cv::imshow( "Blur Image", grayImage );


//    vector<vector<cv::Point> > contours;
//    vector<cv::Vec4i> hierarchy;
//    cv::findContours( grayImage, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE, cv::Point(-1, -1) );
//
//    for (size_t i = 0; i <= contours.size(); ++i)
//    {
//        cv::drawContours(grayImage, contours, -1, cv::Scalar(0, 0, 255), 1, cv::LINE_8, hierarchy);
//    }

    /** 霍夫圆变换 **/
    vector<cv::Vec3f> circles;
    double dp = 2; //
    double minDist = 10;  //两个圆心之间的最小距离
    double  param1 = 100;  //Canny边缘检测的较大阈值
    double  param2 = 100;  //累加器阈值
    int min_radius = 20;  //圆形半径的最小值
    int max_radius = 100;  //圆形半径的最大值

    cv::HoughCircles( grayImage, circles, cv::HOUGH_GRADIENT, dp, minDist, param1, param2, min_radius, max_radius );

    /* 绘制圆心及圆周 */
    vector<cv::Point> centers;
    vector<int> radius;
    for ( size_t i = 0; i <= circles.size(); i++ )
    {
        // 将圆心及半径添加到vector数组中
        centers.push_back( cv::Point(cvRound(circles[i][0]), cvRound(circles[i][1])) ); // 圆心坐标
        radius.push_back( cvRound(circles[i][2]) );    // 半径

        cv::circle( srcImage, centers[i], 3, cv::Scalar(0, 0, 255), -1, cv::LINE_8 );        // 绘制圆心
        cv::circle( srcImage, centers[i], radius[i], cv::Scalar(0, 0, 255), 3, cv::LINE_8 );    //绘制圆周
    }

    // 计算圆心之间距离
    double distance = getDistance( centers[0], centers[1] );

    // 圆心之间连线
    cv::line( srcImage, centers[0], centers[1], cv::Scalar(0, 255, 255), 2, cv::LINE_8 );

    cout << "检测到的圆的数量：" << circles.size() << "\n"
         << "圆心之间的距离为：" << distance << endl;

    cv::imshow( "[Detection Result]", srcImage );

    cv::waitKey(0);

    return 0;
}

/** 求两点间距离 **/
double getDistance( cv::Point point0, cv::Point point1 )
{
    double distance;

    distance = powf( (point1.x - point0.x), 2) + powf((point1.y - point0.y), 2 );
    distance = sqrtf( distance );

    return distance;
}
