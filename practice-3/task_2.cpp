#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main(int argc, char **argv)
{
    //����ԭʼlenaͼ��תΪ�Ҷ�ͼ
    cv::Mat srcImage, grayImage;

    srcImage = cv::imread("images/lena.jpg", cv::IMREAD_COLOR);
    if (srcImage.empty())
	{
        cout << "Cannot read image file";

        return -1;
	}
    cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);

    //ͨ��ֱ��ͼ������ֵ

    /** ��ֵ�ָ� **/
    cv::Mat dstImage;
    //threshΪ�ָ���ֵ��maxValΪ��Ӧ���������ֵ
    double thresh = 57, maxVal = 255;
    // ���ú���threshold()������ֵ�ָ�
    cv::threshold(grayImage, dstImage, thresh, maxVal, cv::THRESH_BINARY);


    cv::imshow("��Source Image��", srcImage);
    cv::imshow("��Threshold Result��", dstImage);

    cv::waitKey(0);

    return 0;
}
