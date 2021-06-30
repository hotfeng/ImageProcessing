#include <opencv2/opencv.hpp>

using namespace std;

int main(int argc, char **argv)
{
    cv::Mat srcImg;
    srcImg = cv::imread("images/lenargb.bmp", cv::IMREAD_COLOR);
    cv::imshow("Lena", srcImg);

    cv::waitKey(0);

    return 0;
}
