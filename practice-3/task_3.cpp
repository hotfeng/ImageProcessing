#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

// ����ͼ���з�������
int calcArea(cv::Mat &img, int rows, int cols);

int main(int argc, char **argv)
{
    //��ȡԭʼͼ���ҶȻ�
    cv::Mat srcImage, grayImage;

    srcImage = cv::imread("images/rectangle.bmp", cv::IMREAD_COLOR);
    if (srcImage.empty())
	{
        cout << "Cannot read image file";

        return -1;
	}
    cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);

    /** ��ֵ�ָ226��matlab��ֱ��ͼ�ó��� **/
    cv::Mat dstImage;
    //threshΪ�ָ���ֵ��maxValΪ��Ӧ���������ֵ
    double thresh = 226, maxVal = 255;
    // ���ú���threshold()������ֵ�ָ�
    cv::threshold(grayImage, dstImage, thresh, maxVal, cv::THRESH_BINARY);

    /** ���㷽����� **/
    const int rows = dstImage.rows;   //ͼ���
    const int cols = dstImage.cols;   //ͼ���

    //�����Զ��庯����ȡ�������
    int totalPixel = calcArea(dstImage, rows, cols);
    cout << "ԭͼ�з������Ϊ��" << totalPixel << endl;

    cv::imshow("Source Image", srcImage);
    cv::imshow("Threshold Result", dstImage);

    cv::waitKey(0);

	return 0;
}

/** ����ͼ���з������� **/
int calcArea(cv::Mat &img, int rows, int cols)
{
    int totalPixel = 0;

    for (int i = 0; i != rows; ++i)
    {
        for (int j = 0; j != cols; ++j)
        {
            // ���ĳ�����ص�ĻҶ�ֵΪ0��������������һ
            if (img.at<uchar>(i, j) == 0)
            {
                ++totalPixel;
            }
        }
    }

    return totalPixel;
}
