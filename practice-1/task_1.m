%% ��ʼ��
close all;
clear;
clc;

%% ���ء�lenargb.bmp������guazi.bmp��ԭʼͼ����ʾ
lenaImg = imread("images/lenargb.bmp");
imshow(lenaImg);
title("lena-initial image");

gzImg = imread("images/guazi.bmp");
figure;	%��һ���´���
imshow(gzImg);
title("guizi-initial image");

%% ��lenaԭͼת��Ϊ�Ҷ�ͼ����ʾ
imgGray = rgb2gray(lenaImg);
figure;
imshow(imgGray);
title("lena-gray image");