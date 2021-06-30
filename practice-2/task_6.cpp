#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

int main(int argc, char **argv)
{
    //加载原始图像
    cv::Mat srcImage = cv::imread("images/desert.jpg", cv::IMREAD_COLOR);
    cv::Mat grayImage, histImage;
    if (!srcImage.data)
    {
        cout << "The image path dose not exist, Please check it!" << endl;
        return false;
    }
    //灰度化处理
    cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);
    cv::imshow("原始灰度图", grayImage);

    //进行直方图均衡化
    cv::equalizeHist(grayImage, histImage);
    cv::imshow("直方图均衡化效果", histImage);
    cv::waitKey(0);

    return 0;
}
