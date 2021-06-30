#include <iostream>
#include <cmath>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;

double getDistance( cv::Point pointO, cv::Point point1 );

int main(void)
{
    /** ��ȡԭͼ���ҶȻ� **/
    cv::Mat srcImage, grayImage;
    srcImage = cv::imread( "images/center_detection.jpg", cv::IMREAD_COLOR );
    cv::cvtColor( srcImage, grayImage, cv::COLOR_BGR2GRAY );
    // ��ʾԭͼ
    cv::imshow( "[Source Image]", srcImage );
    // cv::bitwise_not( grayImage, grayImage );     // ��λȡ��

    // /** ��˹�˲� **/
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

    /** ����Բ�任 **/
    vector<cv::Vec3f> circles;
    double dp = 2; //
    double minDist = 10;  //����Բ��֮�����С����
    double  param1 = 100;  //Canny��Ե���Ľϴ���ֵ
    double  param2 = 100;  //�ۼ�����ֵ
    int min_radius = 20;  //Բ�ΰ뾶����Сֵ
    int max_radius = 100;  //Բ�ΰ뾶�����ֵ

    cv::HoughCircles( grayImage, circles, cv::HOUGH_GRADIENT, dp, minDist, param1, param2, min_radius, max_radius );

    /* ����Բ�ļ�Բ�� */
    vector<cv::Point> centers;
    vector<int> radius;
    for ( size_t i = 0; i <= circles.size(); i++ )
    {
        // ��Բ�ļ��뾶��ӵ�vector������
        centers.push_back( cv::Point(cvRound(circles[i][0]), cvRound(circles[i][1])) ); // Բ������
        radius.push_back( cvRound(circles[i][2]) );    // �뾶

        cv::circle( srcImage, centers[i], 3, cv::Scalar(0, 0, 255), -1, cv::LINE_8 );        // ����Բ��
        cv::circle( srcImage, centers[i], radius[i], cv::Scalar(0, 0, 255), 3, cv::LINE_8 );    //����Բ��
    }

    // ����Բ��֮�����
    double distance = getDistance( centers[0], centers[1] );

    // Բ��֮������
    cv::line( srcImage, centers[0], centers[1], cv::Scalar(0, 255, 255), 2, cv::LINE_8 );

    cout << "��⵽��Բ��������" << circles.size() << "\n"
         << "Բ��֮��ľ���Ϊ��" << distance << endl;

    cv::imshow( "[Detection Result]", srcImage );

    cv::waitKey(0);

    return 0;
}

/** ���������� **/
double getDistance( cv::Point point0, cv::Point point1 )
{
    double distance;

    distance = powf( (point1.x - point0.x), 2) + powf((point1.y - point0.y), 2 );
    distance = sqrtf( distance );

    return distance;
}
