#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;

int main(void)
{
    // ��ȡԭͼ���ҶȻ�
    cv::Mat srcImage, grayImage;
    srcImage = cv::imread( "images/rice.jpg", cv::IMREAD_COLOR );
    cv::cvtColor( srcImage, grayImage, cv::COLOR_BGR2GRAY );

    // ��ȡͼ�񱳾�
    // ��ȡ�ṹԪ�أ��ں˾���/ģ��/��Ĥ��
    cv::Mat background;
    cv::Mat kernel = cv::getStructuringElement( cv::MORPH_ELLIPSE, cv::Size(5, 5), cv::Point(-1, -1) );

    // ��̬ѧ������
    cv::morphologyEx( grayImage, background, cv::MORPH_OPEN, kernel, cv::Point(-1, -1), 7 );
    cv::imshow( "Background", background );


    // ��ȡͼ��ǰ��
    cv::Mat foreground;
    cv::subtract( grayImage, background, foreground );
    cv::imshow( "Foreground", foreground );

    // ��ֵ��-OTSU�㷨
    cv::Mat binaryImg;
    cv::threshold( foreground, binaryImg, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU );
    cv::imshow("Binary foreground", binaryImg);

    // �����ͨ����
    cv::Mat labels, stats, centroids;
    int nccomps = cv::connectedComponentsWithStats( binaryImg, labels, stats, centroids, 8, CV_32S );
    cout << "Total Connected Components Detected: " << nccomps << endl;

    vector<cv::Vec3b> colors(nccomps + 1);
    colors[0] = cv::Vec3b(0, 0, 0); // background pixels remain black.

    for( int i = 1; i < nccomps; i++ )
    {
        colors[i] = cv::Vec3b( rand()%256, rand()%256, rand()%256 );    //Ϊ��i��blob���������⣩���ָ����ɫ
//        if( stats.at<int>(i, cv::CC_STAT_AREA) < 200 )
//            colors[i] = cv::Vec3b(0,0,0); // small regions are painted with black too.
    }

    cv::Mat dstImage = cv::Mat::zeros(srcImage.size(), CV_8UC3);
    for( int y = 0; y < dstImage.rows; y++ )
    {
        for( int x = 0; x < dstImage.cols; x++ )
        {
            int label = labels.at<int>(y, x);
            CV_Assert( 0 <= label && label <= nccomps );

            dstImage.at<cv::Vec3b>(y, x) = colors[label];
        }
    }
    cv::imshow("Detection Result", dstImage);

    cv::waitKey(0);

    return 0;
}
