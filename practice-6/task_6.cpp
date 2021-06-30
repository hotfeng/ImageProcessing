#include <iostream>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main(int,char *argv[])
{
	Mat OriginalImg;

	OriginalImg = imread("TestPhoto (1).jpg", IMREAD_COLOR);//读取原始彩色图像
	if (OriginalImg.empty())  //判断图像对否读取成功
	{
		cout << "错误!读取图像失败\n";
		return -1;
	}
//	imshow("原图", OriginalImg); //显示原始图像
	cout << "Width:" << OriginalImg.rows << "\tHeight:" << OriginalImg.cols << endl;//打印长宽

	Mat ResizeImg;
	if (OriginalImg.cols > 640)
		resize(OriginalImg, ResizeImg, Size(640, 640 * OriginalImg.rows / OriginalImg.cols));
	imshow("尺寸变换图", ResizeImg);

	unsigned char pixelB, pixelG, pixelR;  //记录各通道值
	unsigned char DifMax = 50;             //基于颜色区分的阈值设置
	unsigned char B = 138, G = 63, R = 23; //各通道的阈值设定，针对与蓝色车牌
	Mat BinRGBImg = ResizeImg.clone();  //二值化之后的图像
	int i = 0, j = 0;
	for (i = 0; i < ResizeImg.rows; i++)   //通过颜色分量将图片进行二值化处理
	{
		for (j = 0; j < ResizeImg.cols; j++)
		{
			pixelB = ResizeImg.at<Vec3b>(i, j)[0]; //获取图片各个通道的值
			pixelG = ResizeImg.at<Vec3b>(i, j)[1];
			pixelR = ResizeImg.at<Vec3b>(i, j)[2];

			if (abs(pixelB - B) < DifMax && abs(pixelG - G) < DifMax && abs(pixelR - R) < DifMax)
			{                                           //将各个通道的值和各个通道阈值进行比较
				BinRGBImg.at<Vec3b>(i, j)[0] = 255;     //符合颜色阈值范围内的设置成白色
				BinRGBImg.at<Vec3b>(i, j)[1] = 255;
				BinRGBImg.at<Vec3b>(i, j)[2] = 255;
			}
			else
			{
				BinRGBImg.at<Vec3b>(i, j)[0] = 0;        //不符合颜色阈值范围内的设置为黑色
				BinRGBImg.at<Vec3b>(i, j)[1] = 0;
				BinRGBImg.at<Vec3b>(i, j)[2] = 0;
			}
		}
	}
	imshow("基于颜色信息二值化", BinRGBImg);        //显示二值化处理之后的图像

	Mat BinOriImg;     //形态学处理结果图像
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3)); //设置形态学处理窗的大小
	dilate(BinRGBImg, BinOriImg, element);     //进行多次膨胀操作
	dilate(BinOriImg, BinOriImg, element);
	dilate(BinOriImg, BinOriImg, element);

	erode(BinOriImg, BinOriImg, element);      //进行多次腐蚀操作
	erode(BinOriImg, BinOriImg, element);
	erode(BinOriImg, BinOriImg, element);
	imshow("形态学处理后", BinOriImg);        //显示形态学处理之后的图像

	double length, area, rectArea;     //定义轮廓周长、面积、外界矩形面积
	double rectDegree = 0.0;           //矩形度=外界矩形面积/轮廓面积
	double long2Short = 0.0;           //体态比=长边/短边
	Rect rect;           //外界矩形
	Box2D box, boxTemp;  //外接矩形
	Point2D32f pt[4];    //矩形定点变量
	double axisLong = 0.0, axisShort = 0.0;        //矩形的长边和短边
	double axisLongTemp = 0.0, axisShortTemp = 0.0;//矩形的长边和短边
	double LengthTemp;     //中间变量
	float  angle = 0;      //记录车牌的倾斜角度
	float  angleTemp = 0;
	bool   TestPlantFlag = 0;  //车牌检测成功标志位
	cvtColor(BinOriImg, BinOriImg, CV_BGR2GRAY);   //将形态学处理之后的图像转化为灰度图像
	threshold(BinOriImg, BinOriImg, 100, 255, THRESH_BINARY); //灰度图像二值化
	MemStorage *storage = CreateMemStorage(0);
	Seq * seq = 0;     //创建一个序列,CvSeq本身就是一个可以增长的序列，不是固定的序列
	Seq * tempSeq = CreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint), storage);
	int cnt = FindContours(&(IplImage(BinOriImg)), storage, &seq, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	//第一个参数是IplImage指针类型，将MAT强制转换为IplImage指针类型
	//返回轮廓的数目
	//获取二值图像中轮廓的个数
	cout << "number of contours   " << cnt << endl;  //打印轮廓个数
	for (tempSeq = seq; tempSeq != NULL; tempSeq = tempSeq->h_next)
	{
		length = cvArcLength(tempSeq);       //获取轮廓周长
		area = cvContourArea(tempSeq);       //获取轮廓面积
		if (area > 800 && area < 50000)     //矩形区域面积大小判断
		{
			rect = cvBoundingRect(tempSeq, 1);//计算矩形边界
			boxTemp = cvMinAreaRect2(tempSeq, 0);  //获取轮廓的矩形
			cvBoxPoints(boxTemp, pt);              //获取矩形四个顶点坐标
			angleTemp = boxTemp.angle;                 //得到车牌倾斜角度

			axisLongTemp = sqrt(pow(pt[1].x - pt[0].x, 2) + pow(pt[1].y - pt[0].y, 2));  //计算长轴（勾股定理）
			axisShortTemp = sqrt(pow(pt[2].x - pt[1].x, 2) + pow(pt[2].y - pt[1].y, 2)); //计算短轴（勾股定理）

			if (axisShortTemp > axisLongTemp)   //短轴大于长轴，交换数据
			{
				LengthTemp = axisLongTemp;
				axisLongTemp = axisShortTemp;
				axisShortTemp = LengthTemp;
			}
			else
				angleTemp += 90;
			rectArea = axisLongTemp * axisShortTemp;  //计算矩形的面积
			rectDegree = area / rectArea;     //计算矩形度（比值越接近1说明越接近矩形）

			long2Short = axisLongTemp / axisShortTemp; //计算长宽比
			if (long2Short > 2.2 && long2Short < 3.8 && rectDegree > 0.63 && rectDegree < 1.37 && rectArea > 2000 && rectArea < 50000)
			{
				Mat GuiRGBImg = ResizeImg.clone();
				TestPlantFlag = true;             //检测车牌区域成功
				for (int i = 0; i < 4; ++i)       //划线框出车牌区域
					cvLine(&(IplImage(GuiRGBImg)), cvPointFrom32f(pt[i]), cvPointFrom32f(pt[((i + 1) % 4) ? (i + 1) : 0]), CV_RGB(255, 0, 0));
				imshow("提取车牌结果图", GuiRGBImg);    //显示最终结果图

				box = boxTemp;
				angle = angleTemp;
				axisLong = axisLongTemp;
				axisShort = axisShortTemp;
				cout << "倾斜角度：" << angle << endl;
			}
		}
	}

	waitKey();
	return 0;

}

