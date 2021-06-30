#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main(int argc, char **argv)
{
    // ����ԭͼ���ҶȻ�
    cv::Mat srcImage, grayImage;

    srcImage = cv::imread("images/rectangles.bmp", cv::IMREAD_COLOR);
    cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);

    // ����һ��blob�����
    cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create();

    // ����ؼ��㣻��ʼ���blob
    vector<cv::KeyPoint> keyPoints;
    detector->detect(grayImage, keyPoints);
    cout << "The number of blob: " << keyPoints.size() << endl;

    // ��blob��ԭͼ�л��Ƴ���
    cv::Mat dstImage;
    cv::drawKeypoints(grayImage, keyPoints, dstImage, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    // ��ʾblob
    cv::imshow("��Blob��", dstImage);
    cv::waitKey(0);

	return 0;
}
