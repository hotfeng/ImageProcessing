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

    //�������ͼ�Ĵ�С������
    if (image1.type() != image2.type() || image1.size() != image2.size()){
        cout << "��ͼ���ͻ��С��ͬ" << endl;
        return 1;
    }

    //ͼ��ĸߣ�����
    int numberRows = image1.rows;
    //ͼ��Ŀ�����
    int numberCols = image1.cols;

    //���������ļ�
    image3.create(numberRows, numberCols, image1.type());
    Mat tFront_image, tHidden_image;
    //Ҫ��ʾ��ͼ��
    Mat front_mask(numberRows, numberCols, image1.type(), Scalar(0xF0, 0xF0, 0xF0));
    //Ҫ���ص�ͼ��
    Mat hidden_mask(numberRows, numberCols, image1.type(), Scalar(0xF0, 0xF0, 0xF0));

    //ǰ��ͼ����λ�����(and)����������������ͼ
    //��Ϊ֮ǰ��������Ϊ0xF0�����֮��ֻ����ǰ4��λ
    bitwise_and(image1, front_mask, tFront_image);
    bitwise_and(image2, hidden_mask, tHidden_image);
    //����ÿ����ɫͨ���������4��λ�Ƶ��Ҳ�
    for (int j = 0; j < numberRows; j++) {
        for (int i = 0; i < numberCols; i++) {
            tHidden_image.at<Vec3b>(j, i)[0] = tHidden_image.at<Vec3b>(j, i)[0] >> 4;
            tHidden_image.at<Vec3b>(j, i)[1] = tHidden_image.at<Vec3b>(j, i)[1] >> 4;
            tHidden_image.at<Vec3b>(j, i)[2] = tHidden_image.at<Vec3b>(j, i)[2] >> 4;
        }
    }
    //ǰ��ͼ����λ�Ļ���(or)����������������ͼ
    //Ҫ���ص�ͼ�����Ҳ���ĸ�λ
    bitwise_or(tFront_image, tHidden_image, image3);
    imshow("Org image", image1);
    imshow("Hide image", image2);
    imshow("Steged image", image3);
    //imwrite("D:\\C++\\openCV\\images\\staged-lena.jpg", image3);
    waitKey(0);

    return 0;
}
