#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
typedef std::vector<std::vector<cv::Point>> contoursType;

/* 自动义寻找轮廓函数 */
void myFindContours(cv::Mat srcImg, contoursType& Contours)
{
    cv::Mat grayImg;
    cv::cvtColor(srcImg, grayImg, cv::COLOR_BGR2GRAY);

    cv::Mat binaryImg;
    cv::threshold(grayImg, binaryImg, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(binaryImg, Contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE, cv::Point());
}

int main(void)
{
    cv::Mat tmplImg = cv::imread("images/template_a.jpg", 1);
    cv::Mat matchImg = cv::imread("images/abc.jpg", 1);

    contoursType tmplContours, matchContours;

    myFindContours(tmplImg, tmplContours);
    myFindContours(matchImg, matchContours);

    cv::drawContours(tmplImg, tmplContours, -1, cv::Scalar(0, 0, 255), 1, cv::LINE_8);
    cv::drawContours(matchImg, matchContours, -1, cv::Scalar(255, 0, 0), 2, cv::LINE_8);

    std::vector<double> matchDegree;

    /* 遍历匹配图中的每一个轮廓，计算与模板轮廓的匹配度 */
    for (size_t i = 0; i < matchContours.size(); ++i)
    {
        double tmpDegree = cv::matchShapes(tmplContours[0], matchContours[i], cv::CONTOURS_MATCH_I1, 0.0);
        matchDegree.push_back(tmpDegree);
    }

    for (auto& val : matchDegree)
    {
        cout << "Degree of Match：" << val << endl;
    }

    cv::imshow("Template image", tmplImg);
    cv::imshow("matching image", matchImg);
    cv::waitKey(0);

	return 0;
}
