#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    Mat image1, image2, image3;
    image1 = imread("images/lena.bmp", IMREAD_COLOR);
    image2 = imread("images/911.bmp", IMREAD_COLOR);
    namedWindow("Org image", WINDOW_AUTOSIZE);
    namedWindow("Hide image", WINDOW_AUTOSIZE);
    namedWindow("Steged image", WINDOW_AUTOSIZE);

    //检查两个图的大小与类型
    if (image1.type() != image2.type() || image1.size() != image2.size()){
        cout << "两图类型或大小不同" << endl;
        return 1;
    }

    //图像的高，行数
    int numberRows = image1.rows;
    //图像的宽，列数
    int numberCols = image1.cols;

    //产生加密文件
    image3.create(numberRows, numberCols, image1.type());
    Mat tFront_image, tHidden_image;
    //要显示的图像
    Mat front_mask(numberRows, numberCols, image1.type(), Scalar(0xF0, 0xF0, 0xF0));
    //要隐藏得图像
    Mat hidden_mask(numberRows, numberCols, image1.type(), Scalar(0xF0, 0xF0, 0xF0));

    //前两图进行位的相加(and)处理，结果放入第三张图
    //因为之前声明资料为0xF0，相加之后只保留前4个位
    bitwise_and(image1, front_mask, tFront_image);
    bitwise_and(image2, hidden_mask, tHidden_image);
    //处理每个颜色通道，将左侧4个位移到右侧
    for (int j = 0; j < numberRows; j++) {
        for (int i = 0; i < numberCols; i++) {
            tHidden_image.at<Vec3b>(j, i)[0] = tHidden_image.at<Vec3b>(j, i)[0] >> 4;
            tHidden_image.at<Vec3b>(j, i)[1] = tHidden_image.at<Vec3b>(j, i)[1] >> 4;
            tHidden_image.at<Vec3b>(j, i)[2] = tHidden_image.at<Vec3b>(j, i)[2] >> 4;
        }
    }
    //前两图进行位的互补(or)处理，结果放入第三张图
    //要隐藏的图就是右侧的四个位
    bitwise_or(tFront_image, tHidden_image, image3);
    imshow("Org image", image1);
    imshow("Hide image", image2);
    imshow("Steged image", image3);
    //imwrite("D:\\C++\\openCV\\images\\staged-lena.jpg", image3);
    waitKey(0);

    return 0;
}
