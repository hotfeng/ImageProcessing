%% ��ʼ��
close all;
clear;
clc;

%% ���ء�square.bmp�������лҶȻ�������ֱ��ͼ����ֵ��
srcImage = imread("images/square.bmp");
grayImage = rgb2gray(srcImage);
figure(1);
subplot(121); imshow(srcImage); title("������ԭͼ");
subplot(122); imshow(grayImage); title("�����λҶ�ͼ");

figure(2);
subplot(121); imhist(grayImage);    %����ֱ��ͼ

% T = graythresh(I)������Ҷ�ͼI�е���ֵT
% BW = imbinarize(I,T)��������ֵT�����Ҷ�ͼI�Ķ�ֵͼ��
level = graythresh(grayImage);
BW = imbinarize(grayImage,level);
subplot(122); imshow(BW); title("��ֵ�ָ�Ч��ͼ");

%% �����ֵͼ�������������
totalArea = bwarea(~BW);
fprintf("���������Ϊ��%f\n", totalArea);