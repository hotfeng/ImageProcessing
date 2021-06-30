#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

int main(int argc, char **argv)
{
    //����ԭʼͼ��
    cv::Mat srcImage = cv::imread("images/desert.jpg", cv::IMREAD_COLOR);
    cv::Mat grayImage, histImage;
    if (!srcImage.data)
    {
        cout << "The image path dose not exist, Please check it!" << endl;
        return false;
    }
    //�ҶȻ�����
    cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);
    cv::imshow("ԭʼ�Ҷ�ͼ", grayImage);

    //����ֱ��ͼ���⻯
    cv::equalizeHist(grayImage, histImage);
    cv::imshow("ֱ��ͼ���⻯Ч��", histImage);
    cv::waitKey(0);

    return 0;
}
