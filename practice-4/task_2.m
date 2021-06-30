%% ��ʼ��
close all;
clear;
clc;

%% ��ȡԭͼ���ҶȻ�����
srcImage = imread("images/lenargb.bmp");
figure(1); imshow(srcImage); title("1 Lenaԭͼ");
grayImage = rgb2gray(srcImage);
figure(2); imshow(grayImage); title("2 Lena�Ҷ�ͼ");

%% �������
% Add salt and pepper noise, with a noise density of 0.03, to the grayImage.
noiseImage = imnoise(grayImage,"salt & pepper",0.05);
figure(3); imshow(noiseImage); title("3 Lena����ͼ");

%% ��ֵ�˲� & ��˹�˲�
% Each output pixel contains the median value in a 3-by-3 neighborhood 
% around the corresponding pixel in the input image.
medfiltImage = medfilt2(noiseImage,[3 3]);
figure(4); imshow(medfiltImage); title("4 Lena��ֵ�˲�Ч��ͼ");

% Filter the noiseImage with a Gaussian filter with standard deviation of 2.
gaussFiltImage = imgaussfilt(noiseImage,2);
figure(5); imshow(gaussFiltImage); title("5 Lena��˹�˲�Ч��ͼ");
