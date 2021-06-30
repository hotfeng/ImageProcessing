#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main(int argc, char **argv)
{
    //读入原始lena图并转为灰度图
    cv::Mat srcImage, grayImage;

    srcImage = cv::imread("images/lena.jpg", cv::IMREAD_COLOR);
    if (srcImage.empty())
	{
        cout << "Cannot read image file";

        return -1;
	}
    cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);

    //通过直方图计算阈值

    /** 阈值分割 **/
    cv::Mat dstImage;
    //thresh为分割阈值，maxVal为对应的最大像素值
    double thresh = 57, maxVal = 255;
    // 调用函数threshold()进行阈值分割
    cv::threshold(grayImage, dstImage, thresh, maxVal, cv::THRESH_BINARY);


    cv::imshow("【Source Image】", srcImage);
    cv::imshow("【Threshold Result】", dstImage);

    cv::waitKey(0);

    return 0;
}
