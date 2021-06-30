#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>

int main(void)
{
    cv::VideoCapture cap(0);

    cv::Mat frame, grayImg, binaryImg, dstImg;

    cv::SimpleBlobDetector::Params params;
    cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);
    std::vector<cv::KeyPoint> keypoints;

    while(cap.isOpened())
    {
        cap >> frame;
        cv::cvtColor(frame, grayImg, cv::COLOR_BGR2GRAY);

        cv::threshold(grayImg, binaryImg, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

        // blob detection
        detector->detect(frame, keypoints);
        cv::drawKeypoints(binaryImg, keypoints, dstImg, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

        cv::imshow("Webcam", dstImg);
        if (cv::waitKey(30) == 'q')
            break;
    }

    return 0;
}
