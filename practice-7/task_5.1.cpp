/** 计算轮廓特征，如面积、周长、最小外接距等 **/

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

int main(void)
{
    cv::Mat srcImg = cv::imread("images/handwriting.jpg", 1);
    cv::Mat grayImg;
    cv::cvtColor(srcImg, grayImg, cv::COLOR_BGR2GRAY);

    cv::Mat binaryImg;
    cv::threshold(grayImg, binaryImg, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);


    // 寻找并绘制轮廓
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    double totalArea, totalPerimeter;

    cv::findContours(binaryImg, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point());
    cv::drawContours(srcImg, contours, -1, cv::Scalar(0, 0, 255), 1, cv::LINE_8);

    /* 遍历每一个轮廓 */
    for (size_t i = 0; i < contours.size(); ++i)
    {
        std::vector<cv::Point> tmpContour = contours[i];

        // 寻找外接矩
        cv::Rect bdRect = cv::boundingRect(tmpContour);
        cv::rectangle(srcImg, bdRect, cv::Scalar(0, 255, 0), 2, cv::LINE_8);

        // 寻找最小外接矩
        cv::RotatedRect minRect = cv::minAreaRect(tmpContour);
        cv::Point2f vertex[4];
        minRect.points(vertex);

        for (size_t i = 0; i < 4; ++i)
        {
            cv::line(srcImg, vertex[i], vertex[(i+1) % 4], cv::Scalar(255, 0, 0), 2, cv::LINE_8);
        }

        // 寻找最小外接圆
        cv::Point2f center;
        float radius = 0;

        cv::minEnclosingCircle(tmpContour, center, radius);
        cv::circle(srcImg, center, radius, cv::Scalar(255, 255, 0), 2, cv::LINE_8);

        // 计算轮廓总面积及总周长
        totalArea += cv::contourArea(tmpContour);
        totalPerimeter += cv::arcLength(tmpContour, true);
    }

    cout << "total area = " << totalArea << endl;
    cout << "total perimeter = " << totalPerimeter << endl;


    cv::imshow("contours", srcImg);
    cv::waitKey(0);

	return 0;
}
