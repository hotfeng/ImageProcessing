#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

int main(void)
{
    cv::Mat srcImg = cv::imread("images/pumpkin.jpg", 1);
    cv::resize(srcImg, srcImg, cv::Size(), 0.5, 0.5);
    cv::Mat grayImg;
    cv::cvtColor(srcImg, grayImg, cv::COLOR_BGR2GRAY);

    //cv::blur(grayImg, grayImg, cv::Size(3, 3));

    cv::Mat binaryImg;
    cv::threshold(grayImg, binaryImg, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
    //cv::threshold(grayImg, binaryImg, 240, 255, cv::THRESH_BINARY_INV);

    cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
//    cv::erode(binaryImg, binaryImg, element, cv::Point(), 6);
//    cv::dilate(binaryImg, binaryImg, element, cv::Point(), 2);
    cv::morphologyEx(binaryImg, binaryImg, cv::MORPH_DILATE, element, cv::Point(-1, -1), 10);

//    cv::Mat edgeImg;
//    //cv::equalizeHist(grayImg, edgeImg);
//    cv::Canny(srcImg, edgeImg, 3, 9, 3);
//
//    cv::Mat dstImg;
//    cv::subtract(binaryImg, edgeImg, dstImg);


//    cv::Mat labels, stats, centroids;
//    int nccomps = cv::connectedComponentsWithStats( binaryImg, labels, stats, centroids, 8, CV_32S );
//    cout << "Total Connected Components Detected: " << nccomps << endl;
//
//    vector<cv::Vec3b> colors(nccomps + 1);
//    colors[0] = cv::Vec3b(0, 0, 0); // background pixels remain black.
//
//    for( int i = 1; i <= nccomps; i++ )
//    {
//        colors[i] = cv::Vec3b( rand()%256, rand()%256, rand()%256 );    //为第i个blob（除背景外）随机指定颜色
//    }
//
//    //cv::Mat dstImage = cv::Mat::zeros(srcImage.size(), CV_8UC3);
//    for( int y = 0; y < srcImg.rows; y++ )
//    {
//        for( int x = 0; x < srcImg.cols; x++ )
//        {
//            int label = labels.at<int>(y, x);
//            CV_Assert( 0 <= label && label <= nccomps );
//
//            srcImg.at<cv::Vec3b>(y, x) = colors[label];
//        }
//    }


    cv::imshow("binary", binaryImg);
    cv::imshow("dst", srcImg);

    cv::waitKey(0);

	return 0;
}
