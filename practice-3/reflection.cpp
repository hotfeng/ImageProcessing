#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main(int argc, char **argv)
{
    //�����ɫhsvֵ��������
    cv::Scalar lower_red(156, 43, 46);
    cv::Scalar upper_red(180, 255, 255);

    //ʵ����һ��VideoCapture����
    cv::VideoCapture cap("images/redDetection.mp4");

    //��ʼ��֡��ȡ��Ƶ
    while( cap.isOpened() )
    {
        cv::Mat frame, hsvImage, mask, dstImage;
        //��ȡ��ǰ֡
        cap >> frame;
        //������Ƶ�ߴ�
        cv::resize(frame, frame, cv::Size(0, 0), 0.4, 0.4);

        //��ԭrgb��Ƶ֡ת��Ϊhsv��ʽ
        cv::cvtColor(frame, hsvImage, cv::COLOR_BGR2HSV);
        //��ȡλ�ں�ɫhsvֵ֮�����Ĥmask
        cv::inRange(hsvImage, lower_red, upper_red, mask);

        //��ԭʼ��Ƶ֡��mask��Ĥ�������ơ��롱����
        cv::bitwise_and(frame, frame, dstImage, mask);


        cv::imshow("[Source Image]", frame);
        cv::imshow("[result(Recognize Red)]", dstImage);

        //ÿ��50�����ȡ��һ֡������ESC���˳�
        if (cv::waitKey(50) == 27)
        {
            break;
        }
    }

    return 0;
}
