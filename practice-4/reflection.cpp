#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <cmath>

using namespace std;

double getdistCenter(double point_x1, double point_y1, double point_x2, double point_y2);

int main(int argc, char **argv)
{
    /** ����ԭͼ��תΪ�Ҷ�ͼ **/
    cv::Mat srcImage, grayImage;

    srcImage = cv::imread("images/detect_circles.jpg", cv::IMREAD_COLOR);
    cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);
    cv::imshow("Source Image", srcImage);

    /** ��ֵ�ָתΪ��ֵͼ **/
    cv::Mat thresholdImage;

    cv::threshold(grayImage, thresholdImage, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::imshow("Threshold Segmentation ", thresholdImage);
    //cv::GaussianBlur(grayImage, thresholdImage, cv::Size(5, 5), 0, 0);

    /**
        ����Բ�任
        void cv:HoughCircles(InputArray image, outputArray circles, int method, double dp, double ,
                             double param1, double param2, int minRadius, int maxRadius)

        @circles���ҵ���Բ���������������ÿ��Ԫ��Ϊ������3����������Ԫ�أ�x,y,radius��������
        @method����ⷽ���������õ������ݶȷ��ĸĽ��� cv::HOUGH_GRADIENT_ALT
        @dp���ۼ����ֱ�����ͼ��ֱ��ʵķ��ȣ�dp = 2��ʾ�ۼ����Ŀ�Ⱥ͸߶�������ͼ���һ��
        @minDist����⵽��Բ��֮�����С���룻
        @param1�����ݵ�method�еĵ�һ������������HOUGH_GRADIENT��HOUGH_GRADIENT_ALT�����Ǵ��ݸ�Canny��Ե�������������ֵ�еĽϸ���ֵ
        @param2�����ݵ�method�еĵڶ�����������HOUGH_GRADIENT_ALT�㷨������£�����Բ�� "perfectness" �����������Ҫ����С��Բ���ɽ�����Ϊ0.9���С
        @minRadius������⵽��Բ����С�뾶��
        @maxRadius������⵽��Բ�����뾶
    **/
    vector<cv::Vec3f> circles;
    cv::HoughCircles(thresholdImage, circles, cv::HOUGH_GRADIENT_ALT, 2, 10, 200, 0.9);

    if (!circles.empty())
    {
        for (size_t i = 0; i < circles.size(); ++i)
        {
            cv::Vec3i circle = circles[i];
            // ��i��Բ��Բ��
            cv::Point center(circle[0], circle[1]);
            // ��i��Բ�İ뾶
            //int radius = cvRound(circles[i][2]);
            int radius = circle[2];

            //����Բ�ģ�����ɫ��
            cv::circle(srcImage, center, 3, cv::Scalar::all(255), -1, cv::LINE_8, 0);
            // ����Բ����
            cv::circle(srcImage, center, radius, cv::Scalar(0, 0, 255), 2, cv::LINE_8, 0);

            printf("��%d��Բ��Բ������Ϊ��(%d, %d)\t\t", i + 1, center.x, center.y);
            printf("�뾶Ϊ��%f\n", circles[i][2]);
        }

        double distance = getdistCenter(circles[0][0], circles[0][1], circles[1][0], circles[1][1]);
        cout << "\n��ԲԲ��֮�����Ϊ��" << distance << endl;

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


/** ����Բ�ľ��� **/
double getdistCenter(double point_x1, double point_y1, double point_x2, double point_y2)
{
    double distance;
    distance = pow((point_x2 - point_x1), 2) + pow((point_y2 - point_y1), 2);
    distance = sqrt(distance);

    return distance;
}
