#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main(int argc, char **argv)
{
    //定义红色hsv值的上下限
    cv::Scalar lower_red(156, 43, 46);
    cv::Scalar upper_red(180, 255, 255);

    //实例化一个VideoCapture对象
    cv::VideoCapture cap("images/redDetection.mp4");

    //开始按帧读取视频
    while( cap.isOpened() )
    {
        cv::Mat frame, hsvImage, mask, dstImage;
        //读取当前帧
        cap >> frame;
        //调整视频尺寸
        cv::resize(frame, frame, cv::Size(0, 0), 0.4, 0.4);

        //将原rgb视频帧转化为hsv格式
        cv::cvtColor(frame, hsvImage, cv::COLOR_BGR2HSV);
        //获取位于红色hsv值之间的掩膜mask
        cv::inRange(hsvImage, lower_red, upper_red, mask);

        //将原始视频帧与mask掩膜做二进制“与”操作
        cv::bitwise_and(frame, frame, dstImage, mask);


        cv::imshow("[Source Image]", frame);
        cv::imshow("[result(Recognize Red)]", dstImage);

        //每隔50毫秒读取下一帧，按“ESC”退出
        if (cv::waitKey(50) == 27)
        {
            break;
        }
    }

    return 0;
}
