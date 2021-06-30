#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;

int main(int argc, char **argv)
{
    cv::Mat srcImage = cv::imread("images/rectangle_2.bmp", 0);
    cv::Mat threshImage = cv::imread("images/seg.jpg", 0);

    int srcArea = 0, threshArea = 0;

    for (int i = 0; i != srcImage.rows; ++i)
    {
        for (int j = 0; j != srcImage.cols; ++j)
        {
            if (srcImage.at<uchar>(i, j) == 0)
            {
                ++srcArea;
            }
        }
    }

    for (int i = 0; i != threshImage.rows; ++i)
    {
        for (int j = 0; j != threshImage.cols; ++j)
        {
            if (threshImage.at<uchar>(i, j) == 0)
            {
                ++threshArea;
            }
        }
    }

    cout << "The area of srcImage: " << srcArea << endl;
    cout << "The area of threshImage: " << threshArea << endl;

    cv::imshow("1", srcImage);
    cv::imshow("2", threshImage);

    cv::waitKey(0);

	return 0;
}
