#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main()
{
    //�������Ź���
    Mat srcImage_1 = imread("images/Japan.jpg");
    Mat srcImage_2 = imread("images/China.jpg");

    if (!srcImage_1.data)
        return -1;

    //��ͼ�������������
    std::vector<Mat> imgs;
    imgs.push_back(srcImage_1);
    imgs.push_back(srcImage_2);

    for (int i = 0; i != imgs.size(); ++i)
    {
        //�Ҷȱ任����˹�˲�
        Mat grayImage;
        cvtColor(imgs[i], grayImage, COLOR_RGB2GRAY);
        GaussianBlur(grayImage, grayImage, Size(7, 7), 2, 2);

        //����Բ�任
        std::vector<Vec3f> circles;
        HoughCircles(grayImage, circles, HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);
        if (circles.size() != 0)
        {
            //��ԭʼͼ���л������֣�pΪ������ʼ��
            cv::putText(imgs[i], "Japan", Point(200, 100), cv::FONT_HERSHEY_TRIPLEX, 0.8, cv::Scalar(255, 200, 200), 2);
        }
        else
        {
            cv::putText(imgs[i], "China", Point(200, 100), cv::FONT_HERSHEY_TRIPLEX, 0.8, cv::Scalar(255, 200, 200), 2);

        }

        imshow("��Ч��ͼ��", imgs[i]);
        waitKey(0);
    }

    return 0;
}

