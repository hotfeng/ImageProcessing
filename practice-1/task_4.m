%% ��ʼ��
close all;
clear;
clc;

%% ����һ���հ���ά���飬����ÿһ������ֵ������rά��ֵ��Ϊ255
Mat = zeros(100,100,3);
for i = 1:100
    for j = 1:100
        Mat(i,j,1) = 255;
    end
end

%% ��ʾ��ɫͼ�񲢱���Ϊ.bmp�ļ�
imshow(Mat);
imwrite(Mat,"images/red.bmp")