#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main(int argc, char **argv)
{
    // 加载原图并灰度化
    cv::Mat srcImage, grayImage;

    srcImage = cv::imread("images/rectangles.bmp", cv::IMREAD_COLOR);
    cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);

    // 定义一个blob检测器
    cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create();

    // 定义关键点；开始检测blob
    vector<cv::KeyPoint> keyPoints;
    detector->detect(grayImage, keyPoints);
    cout << "The number of blob: " << keyPoints.size() << endl;

    // 将blob在原图中绘制出来
    cv::Mat dstImage;
    cv::drawKeypoints(grayImage, keyPoints, dstImage, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    // 显示blob
    cv::imshow("【Blob】", dstImage);
    cv::waitKey(0);

	return 0;
}
