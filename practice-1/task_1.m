%% 初始化
close all;
clear;
clc;

%% 加载“lenargb.bmp”及“guazi.bmp”原始图像并显示
lenaImg = imread("images/lenargb.bmp");
imshow(lenaImg);
title("lena-initial image");

gzImg = imread("images/guazi.bmp");
figure;	%打开一个新窗口
imshow(gzImg);
title("guizi-initial image");

%% 将lena原图转化为灰度图并显示
imgGray = rgb2gray(lenaImg);
figure;
imshow(imgGray);
title("lena-gray image");