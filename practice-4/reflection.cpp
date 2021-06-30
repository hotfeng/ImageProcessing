#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <cmath>

using namespace std;

double getdistCenter(double point_x1, double point_y1, double point_x2, double point_y2);

int main(int argc, char **argv)
{
    /** 加载原图并转为灰度图 **/
    cv::Mat srcImage, grayImage;

    srcImage = cv::imread("images/detect_circles.jpg", cv::IMREAD_COLOR);
    cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);
    cv::imshow("Source Image", srcImage);

    /** 阈值分割，转为二值图 **/
    cv::Mat thresholdImage;

    cv::threshold(grayImage, thresholdImage, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::imshow("Threshold Segmentation ", thresholdImage);
    //cv::GaussianBlur(grayImage, thresholdImage, cv::Size(5, 5), 0, 0);

    /**
        霍夫圆变换
        void cv:HoughCircles(InputArray image, outputArray circles, int method, double dp, double ,
                             double param1, double param2, int minRadius, int maxRadius)

        @circles：找到的圆的输出向量；其中每个元素为包含着3个浮点数子元素（x,y,radius）的向量
        @method：检测方法；这里用到霍夫梯度法的改进版 cv::HOUGH_GRADIENT_ALT
        @dp：累加器分辨率与图像分辨率的反比；dp = 2表示累加器的宽度和高度是输入图像的一半
        @minDist：检测到的圆心之间的最小距离；
        @param1：传递到method中的第一个参数；对于HOUGH_GRADIENT和HOUGH_GRADIENT_ALT，它是传递给Canny边缘检测器的两个阈值中的较高阈值
        @param2：传递到method中的第二个参数；在HOUGH_GRADIENT_ALT算法的情况下，这是圆的 "perfectness" 度量。如果想要检测较小的圆，可将其设为0.9或更小
        @minRadius：所检测到的圆的最小半径；
        @maxRadius：所检测到的圆的最大半径
    **/
    vector<cv::Vec3f> circles;
    cv::HoughCircles(thresholdImage, circles, cv::HOUGH_GRADIENT_ALT, 2, 10, 200, 0.9);

    if (!circles.empty())
    {
        for (size_t i = 0; i < circles.size(); ++i)
        {
            cv::Vec3i circle = circles[i];
            // 第i个圆的圆心
            cv::Point center(circle[0], circle[1]);
            // 第i个圆的半径
            //int radius = cvRound(circles[i][2]);
            int radius = circle[2];

            //绘制圆心（填充白色）
            cv::circle(srcImage, center, 3, cv::Scalar::all(255), -1, cv::LINE_8, 0);
            // 绘制圆轮廓
            cv::circle(srcImage, center, radius, cv::Scalar(0, 0, 255), 2, cv::LINE_8, 0);

            printf("第%d个圆的圆心坐标为：(%d, %d)\t\t", i + 1, center.x, center.y);
            printf("半径为：%f\n", circles[i][2]);
        }

        double distance = getdistCenter(circles[0][0], circles[0][1], circles[1][0], circles[1][1]);
        cout << "\n两圆圆心之间距离为：" << distance << endl;

        cv::namedWindow("Circles Detection", cv::WINDOW_AUTOSIZE);
        cv::imshow("Circles Detection", srcImage);
    }

    else
    {
        cout << "No circles found!" << endl;
        return EXIT_FAILURE;
    }

    cv::waitKey(0);

	return 0;
}


/** 计算圆心距离 **/
double getdistCenter(double point_x1, double point_y1, double point_x2, double point_y2)
{
    double distance;
    distance = pow((point_x2 - point_x1), 2) + pow((point_y2 - point_y1), 2);
    distance = sqrt(distance);

    return distance;
}
