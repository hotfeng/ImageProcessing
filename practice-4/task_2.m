%% 初始化
close all;
clear;
clc;

%% 读取原图并灰度化处理
srcImage = imread("images/lenargb.bmp");
figure(1); imshow(srcImage); title("1 Lena原图");
grayImage = rgb2gray(srcImage);
figure(2); imshow(grayImage); title("2 Lena灰度图");

%% 添加噪声
% Add salt and pepper noise, with a noise density of 0.03, to the grayImage.
noiseImage = imnoise(grayImage,"salt & pepper",0.05);
figure(3); imshow(noiseImage); title("3 Lena噪声图");

%% 中值滤波 & 高斯滤波
% Each output pixel contains the median value in a 3-by-3 neighborhood 
% around the corresponding pixel in the input image.
medfiltImage = medfilt2(noiseImage,[3 3]);
figure(4); imshow(medfiltImage); title("4 Lena中值滤波效果图");

% Filter the noiseImage with a Gaussian filter with standard deviation of 2.
gaussFiltImage = imgaussfilt(noiseImage,2);
figure(5); imshow(gaussFiltImage); title("5 Lena高斯滤波效果图");
