#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;

int main(void)
{
    // 读取原图并灰度化
    cv::Mat srcImage, grayImage;
    srcImage = cv::imread( "images/rice.jpg", cv::IMREAD_COLOR );
    cv::cvtColor( srcImage, grayImage, cv::COLOR_BGR2GRAY );

    // 获取图像背景
    // 获取结构元素（内核矩阵/模板/掩膜）
    cv::Mat background;
    cv::Mat kernel = cv::getStructuringElement( cv::MORPH_ELLIPSE, cv::Size(5, 5), cv::Point(-1, -1) );

    // 形态学开操作
    cv::morphologyEx( grayImage, background, cv::MORPH_OPEN, kernel, cv::Point(-1, -1), 7 );
    cv::imshow( "Background", background );


    // 获取图像前景
    cv::Mat foreground;
    cv::subtract( grayImage, background, foreground );
    cv::imshow( "Foreground", foreground );

    // 二值化-OTSU算法
    cv::Mat binaryImg;
    cv::threshold( foreground, binaryImg, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU );
    cv::imshow("Binary foreground", binaryImg);

    // 检测连通区域
    cv::Mat labels, stats, centroids;
    int nccomps = cv::connectedComponentsWithStats( binaryImg, labels, stats, centroids, 8, CV_32S );
    cout << "Total Connected Components Detected: " << nccomps << endl;

    vector<cv::Vec3b> colors(nccomps + 1);
    colors[0] = cv::Vec3b(0, 0, 0); // background pixels remain black.

    for( int i = 1; i < nccomps; i++ )
    {
        colors[i] = cv::Vec3b( rand()%256, rand()%256, rand()%256 );    //为第i个blob（除背景外）随机指定颜色
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
