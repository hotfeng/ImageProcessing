#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(void)
{
    cv::Mat sceneImg, grayScene, equalImg;

    sceneImg = cv::imread("images/scene.jpg", 1);
    cv::cvtColor(sceneImg, grayScene, cv::COLOR_BGR2GRAY);
    cv::imshow("gray image", grayScene);

    /* 直方图均衡化 */
    // 通过拉伸像素强度分布来增强图像对比度
    cv::equalizeHist(grayScene, equalImg);
    cv::imshow("equalization", equalImg);


    /* 模板匹配 */
    cv::Mat templImg = cv::imread("images/template.jpg", 1);
    cv::Mat srcImg = cv::imread("images/person.jpg", 1);

    // 创建映射图像
    cv::Mat resImg;
    int resCols = srcImg.cols - templImg.cols + 1;
    int resRows = srcImg.rows - templImg.rows + 1;
    resImg.create(resCols, resRows, CV_32FC1);

    // 模板匹配及标准化
    cv::matchTemplate(srcImg, templImg, resImg, cv::TM_CCOEFF);
    cv::normalize(resImg, resImg, 0, 1, cv::NORM_MINMAX, -1);

    // 定位边界框的位置
    double minValue, maxValue;
    cv::Point minLoc, maxLoc;
	cv::Point matchLoc;
	cv::minMaxLoc(resImg, &minValue, &maxValue, &minLoc, &maxLoc, cv::Mat());

	// 绘制边界框
    cv::rectangle(srcImg, maxLoc, cv::Point(maxLoc.x + templImg.cols, maxLoc.y + templImg.rows),cv::Scalar(0, 0, 255));

    cv::imshow("result for detection", srcImg);

    cv::waitKey(0);

	return 0;
}
