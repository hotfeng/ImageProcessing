# include <opencv2/opencv.hpp>
# include <opencv2/imgproc/imgproc.hpp>
# include <opencv2/highgui/highgui.hpp>

using namespace std;

int main(int argc, char **argv)
{
    cv::Mat srcImage = cv::imread("images/flaw1.png", cv::IMREAD_COLOR);

    cv::namedWindow("flaw1", cv::WINDOW_NORMAL);
    cv::imshow("flaw1", srcImage);
    cv::waitKey(0);

    return 0;
}
