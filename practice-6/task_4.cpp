#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>

using namespace std;

int main(void)
{
    cv::Mat srcImg, grayImg;
    srcImg = cv::imread("images/face.jpg", cv::IMREAD_COLOR);
    cv::cvtColor(srcImg, grayImg, cv::COLOR_BGR2GRAY);

    // ���������������������棬'.xml'�ļ������ѵ����������������
    cv::CascadeClassifier face_detector;
    face_detector.load("data/haarcascade_frontalface_default.xml");
    if (face_detector.empty())
    {
        cerr << "ERROR! Unable load CascadeClassifier." << endl;
        return -1;
    }

    //��ȡѵ������ԭʼ�ߴ磬��Ϊ����������С�ߴ磬�����ܵõ���ѵļ��Ч�������Ǳ���ģ�
	cv::Size original_size = face_detector.getOriginalWindowSize();
	std::vector<cv::Rect> faces;

	//���ж�߶��������
	face_detector.detectMultiScale(grayImg, faces, 1.5, 7, 0, original_size);
    for (size_t i = 0; i <= faces.size(); ++i)
    {
        // ���Ƴ�ÿһ����⵽������
        cv::rectangle(srcImg, faces[i], cv::Scalar(0, 0, 255), 2, cv::LINE_8, 0);
    }

    cv::imshow("Face Detection", srcImg);

    cv::waitKey(0);


	return 0;
}
