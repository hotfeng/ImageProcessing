/*
	�����沿��⣺�������۾������ӡ���
	����׼ȷ�������ڷ�����
*/

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

void detectFaces(Mat &img, vector<Rect> &faces, const string& cascade_path);
void detectFacialFeatures(Mat &img, vector<Rect> faces,
                          const string& eye_cascade, const string& nose_cascade, const string& mouth_cascade);

void detectEyes(Mat &img, vector<Rect> &eyes, const string& cascade_path);
void detectNose(Mat &img, vector<Rect> &nose, const string& cascade_path);
void detectMouth(Mat &img, vector<Rect> &mouth, const string& cascade_path);

int main(int argc, char** argv)
{
    CommandLineParser parser(argc, argv, "{help h||}{@input||The path of input image.}");
    const string input_image_path = parser.get<string>("@input");

	vector<string> cascade_path = {"data/haarcascade_frontalface_default.xml",
                                   "data/haarcascade_eye.xml",
                                   "data/haarcascade_mcs_nose.xml",
                                   "data/haarcascade_mcs_mouth.xml"};

	Mat img, imgGray;
	img = imread(input_image_path);
	if (img.empty())
	{
		printf("can't open image\n");
		return -1;
	}

	cvtColor(img, imgGray, COLOR_BGR2GRAY);	//ת���ɻҶ�ͼ���ӿ�����ʶ����ٶ�
	equalizeHist(imgGray, imgGray);		//ֱ��ͼ���⻯

	//����������沿����
	vector<Rect> faces;
	detectFaces(img, faces, cascade_path[0]);
	detectFacialFeatures(img, faces, cascade_path[1], cascade_path[2], cascade_path[3]);

    resize(img, img, Size(), 0.5, 0.5);

	namedWindow("Result", WINDOW_NORMAL);
	imshow("Result", img);

	waitKey(0);
	destroyAllWindows();

	return 0;
}

/** ����������� **/
void detectFaces(Mat &img, vector<Rect> &faces, const string& cascade_path)
{
	CascadeClassifier face_cascade;

	face_cascade.load(cascade_path);
	if (face_cascade.empty())
	{
		printf("can't load face cascade file\n");
		return;
	}

	face_cascade.detectMultiScale(img, faces, 1.1, 3, 0, Size(30, 30));
	return;
}

/** �������������Ŀ�ǿڣ�����ǳ� **/
void detectFacialFeatures(Mat &img, vector<Rect> faces,
                          const string& eye_cascade, const string& nose_cascade, const string& mouth_cascade)
{
	printf("face_size = %zd\n", faces.size());

	for (int i = 0; i < faces.size(); i++)
	{
		Rect face = faces[i];
		rectangle(img, Point(face.x, face.y), Point(face.x + face.width, face.y + face.height), Scalar(255, 0, 0), 2, 4);

		//�۾������Ӻ���ͽ�������������Ȥ�����򣩱���⵽��
		Mat ROI = img(Rect(face.x, face.y, face.width, face.height));

		//�ж��۾������Ӻ�����Ƿ�ȫ������⵽
		bool is_full_detection = false;
		if ((!eye_cascade.empty()) && (!nose_cascade.empty()) && (!mouth_cascade.empty()))
		{
			is_full_detection = true;
		}

		//�û��ṩ�ķ��������Լ���۾�
		if (!eye_cascade.empty())
		{
			vector<Rect> eyes;
			detectEyes(ROI, eyes, eye_cascade);

			//��ǵ����۾����������Ӧ
			printf("eyes_size = %zd\n", eyes.size());
			for (int i = 0; i < eyes.size(); i++)
			{
				Rect e = eyes[i];
				circle(ROI, Point(e.x + e.width / 2, e.y + e.height / 2), 3, Scalar(0, 255, 0), -1, 8);
				//rectangle(ROI, Point(e.x, e.y), Point(e.x + e.width, e.y + e.height), Scalar(0, 255, 0), 1, 8);
			}
		}

		//�û��ṩ�ķ��������Լ�����
		double nose_center_height = 0;
		if (!nose_cascade.empty())
		{
			vector <Rect> nose;
			detectNose(ROI, nose, nose_cascade);

			//��ǵ�����ӵ��������Ӧ
			printf("nose_size = %zd\n", nose.size());
			for (int i = 0; i < nose.size(); i++)
			{
				Rect n = nose[i];
				circle(ROI, Point(n.x + n.width / 2, n.y + n.height / 2), 3, Scalar(0, 255, 0), -1, 8);
				nose_center_height = (n.y + n.height / 2);

			}
		}

		//�û��ṩ�ķ��������Լ�����
		double mouth_center_height = 0;
		if (!mouth_cascade.empty())
		{
			vector<Rect> mouth;
			detectMouth(ROI, mouth, mouth_cascade);

			printf("mouth.size = %zd\n", mouth.size());
			for (int i = 0; i < mouth.size(); i++)
			{
				Rect m = mouth[i];
				mouth_center_height = (m.y + m.height / 2);

				if (is_full_detection && (mouth_center_height > nose_center_height))
				{
					rectangle(ROI, Point(m.x, m.y), Point(m.x + m.width, m.y + m.height), Scalar(0, 255, 0), 1, 4);
				}
				else if (is_full_detection && (mouth_center_height <= nose_center_height))
				{
					continue;
				}
				else
				{
					rectangle(ROI, Point(m.x, m.y), Point(m.x + m.width, m.y + m.height), Scalar(0, 255, 0), 1, 4);
				}
			}
		}
	}

	return;
}

void detectEyes(Mat &img, vector<Rect> &eyes, const string& cascade_path)
{
	CascadeClassifier eyes_cascade;

	eyes_cascade.load(cascade_path);

	eyes_cascade.detectMultiScale(img, eyes, 1.20, 5, 0, Size(30, 30));

	return;
}

void detectNose(Mat &img, vector<Rect> &nose, const string& cascade_path)
{
	CascadeClassifier nose_cascade;

	nose_cascade.load(cascade_path);

	nose_cascade.detectMultiScale(img, nose, 1.20, 5, 0, Size(30, 30));

	return;
}

void detectMouth(Mat &img, vector<Rect> &mouth, const string& cascade_path)
{
	CascadeClassifier mouth_cascade;

	mouth_cascade.load(cascade_path);

	mouth_cascade.detectMultiScale(img, mouth, 1.20, 5, 0, Size(30, 30));

	return;
}
