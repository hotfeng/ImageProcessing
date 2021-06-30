%% 初始化
close all;
clear;
clc;

%% 加载“square.bmp”并进行灰度化，计算直方图，阈值化
srcImage = imread("images/square.bmp");
grayImage = rgb2gray(srcImage);
figure(1);
subplot(121); imshow(srcImage); title("正方形原图");
subplot(122); imshow(grayImage); title("正方形灰度图");

figure(2);
subplot(121); imhist(grayImage);    %绘制直方图

% T = graythresh(I)：计算灰度图I中的阈值T
% BW = imbinarize(I,T)：根据阈值T创建灰度图I的二值图像
level = graythresh(grayImage);
BW = imbinarize(grayImage,level);
subplot(122); imshow(BW); title("阈值分割效果图");

%% 计算二值图像中正方形面积
totalArea = bwarea(~BW);
fprintf("正方形面积为：%f\n", totalArea);