#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

// 计算图像中方块的面积
int calcArea(cv::Mat &img, int rows, int cols);

int main(int argc, char **argv)
{
    //读取原始图并灰度化
    cv::Mat srcImage, grayImage;

    srcImage = cv::imread("images/rectangle.bmp", cv::IMREAD_COLOR);
    if (srcImage.empty())
	{
        cout << "Cannot read image file";

        return -1;
	}
    cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);

    /** 阈值分割（226由matlab中直方图得出） **/
    cv::Mat dstImage;
    //thresh为分割阈值，maxVal为对应的最大像素值
    double thresh = 226, maxVal = 255;
    // 调用函数threshold()进行阈值分割
    cv::threshold(grayImage, dstImage, thresh, maxVal, cv::THRESH_BINARY);

    /** 计算方块面积 **/
    const int rows = dstImage.rows;   //图像高
    const int cols = dstImage.cols;   //图像宽

    //调用自定义函数求取方块面积
    int totalPixel = calcArea(dstImage, rows, cols);
    cout << "原图中方块面积为：" << totalPixel << endl;

    cv::imshow("Source Image", srcImage);
    cv::imshow("Threshold Result", dstImage);

    cv::waitKey(0);

	return 0;
}

/** 计算图像中方块的面积 **/
int calcArea(cv::Mat &img, int rows, int cols)
{
    int totalPixel = 0;

    for (int i = 0; i != rows; ++i)
    {
        for (int j = 0; j != cols; ++j)
        {
            // 如果某个像素点的灰度值为0，则总像素数加一
            if (img.at<uchar>(i, j) == 0)
            {
                ++totalPixel;
            }
        }
    }

    return totalPixel;
}
