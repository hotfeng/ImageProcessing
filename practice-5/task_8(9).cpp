#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

int main(int argc, char **argv)
{
    /** 加载原图并转为灰度图 **/
    cv::Mat srcImage, grayImage;

    srcImage = cv::imread("images/shortest_dist.jpg", cv::IMREAD_COLOR);
    cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);
    cv::imshow("Source Image", srcImage);

    /** 阈值分割，转为二值图 **/
    cv::Mat thresholdImage;
    cv::threshold(grayImage, thresholdImage, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    /** 查找轮廓 **/
    cv::Mat dstImage = srcImage.clone();
    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;

    cv::findContours(thresholdImage, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point());
    for( size_t i = 1; i< contours.size(); i++ )
    {
        //cv::drawContours(dstImage, contours, int(i), cv::Scalar(0, 255, 0), 2, cv::LINE_8, hierarchy, 0, cv::Point());
        // 外部矩形边界
        cv::Rect rect = cv::boundingRect(contours[i]);
        cv::rectangle(dstImage, rect, cv::Scalar(0, 255, 255), 2, cv::LINE_8);

        // 最小包围矩阵
        cv::RotatedRect rrt = cv::minAreaRect(contours[i]);
        cv::Point2f pts[4];
        rrt.points(pts);

        //绘制旋转矩形与中心位置
        for (int i = 0; i < 4; i++)
        {
            cv::line(dstImage, pts[i % 4], pts[(i + 1) % 4], cv::Scalar(0, 0, 255), 2, 8, 0);
        }
        cv::Point2f center = rrt.center;
        cv::circle(dstImage, center, 2, cv::Scalar(255, 0, 0), 2, 8, 0);
    }

    cv::imshow("RotatedRect", dstImage);

    cv::waitKey(0);

    return 0;
}
