#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;

int main(int argc, char** argv)
{
    cv::CommandLineParser parser( argc, argv, "{@input|0|The source of camera.}" );
    int indexCamera = parser.get<int> ( "@input" );

    cv::VideoCapture cap( indexCamera );
    if ( !cap.isOpened() )
    {
        cerr << "Cannot open the camera." << endl;
        return -1;
    }

    cv::Mat frame, grayImg, binaryImg;
    cv::namedWindow("result", cv::WINDOW_AUTOSIZE);
    while ( cap.isOpened() )
    {
        cap >> frame;
        cv::cvtColor(frame, grayImg, cv::COLOR_BGR2GRAY);

        cv::threshold(grayImg, binaryImg, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

        cv::Mat labels, stats, centroids;
        int nccomps = cv::connectedComponentsWithStats( binaryImg, labels, stats, centroids, 8, CV_32S );
        //cout << "Total Connected Components Detected: " << nccomps << endl;

        vector<cv::Vec3b> colors(nccomps + 1);
        colors[0] = cv::Vec3b(0, 0, 0); // background pixels remain black.

        for( int i = 1; i <= nccomps; i++ )
        {
            colors[i] = cv::Vec3b( rand()%256, rand()%256, rand()%256 );    //为第i个blob（除背景外）随机指定颜色
        }

        //cv::Mat dstImage = cv::Mat::zeros(srcImage.size(), CV_8UC3);
        for( int y = 0; y < frame.rows; y++ )
        {
            for( int x = 0; x < frame.cols; x++ )
            {
                int label = labels.at<int>(y, x);
                CV_Assert( 0 <= label && label <= nccomps );

                frame.at<cv::Vec3b>(y, x) = colors[label];
            }
        }

        cv::imshow("result", frame);
        if ( cv::waitKey(30) == 'q' )
        {
            break;
        }

    }


	return 0;
}
