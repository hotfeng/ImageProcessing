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

    // 导入人脸级联分类器引擎，'.xml'文件里包含训练出来的人脸特征
    cv::CascadeClassifier face_detector;
    face_detector.load("data/haarcascade_frontalface_default.xml");
    if (face_detector.empty())
    {
        cerr << "ERROR! Unable load CascadeClassifier." << endl;
        return -1;
    }

    //获取训练集的原始尺寸，作为分类器的最小尺寸，这样能得到最佳的检测效果（不是必须的）
	cv::Size original_size = face_detector.getOriginalWindowSize();
	std::vector<cv::Rect> faces;

	//进行多尺度人脸检测
	face_detector.detectMultiScale(grayImg, faces, 1.5, 7, 0, original_size);
    for (size_t i = 0; i <= faces.size(); ++i)
    {
        // 绘制出每一个检测到的人脸
        cv::rectangle(srcImg, faces[i], cv::Scalar(0, 0, 255), 2, cv::LINE_8, 0);
    }

    cv::imshow("Face Detection", srcImg);

    cv::waitKey(0);


	return 0;
}
