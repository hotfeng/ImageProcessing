%% 初始化
close all;
clear;
clc;

%% 读取“lenargb.bmp”与“guazi.bmp”并灰度化
lenaImage = imread("images/lenargb.bmp");
lenaGray = rgb2gray(lenaImage);

gzImage = imread("images/guazi.bmp");
gzGray = rgb2gray(gzImage);

%% 使用matlab函数提取直方图信息
figure(1)
subplot(121); imshow(lenaGray); title("1 lena灰度图");
subplot(122); imhist(lenaGray); title("2 lena直方图");

figure(2);
subplot(121); imshow(gzGray); title("1 瓜子灰度图");
subplot(122); imhist(gzGray); title("2 瓜子直方图");

%% 使用自定义函数提取直方图信息
lenaHist = myHist(lenaGray);
gzHist = myHist(gzGray);
figure(3);
subplot(121); plot(lenaHist); title("1 lena直方图")
subplot(122); plot(gzHist); title("2 瓜子直方图")


function histNum = myHist(grayImage)
    [width,height,~] = size(grayImage);
    histNum = zeros(256,1); %直方图画布
    for i=1:width
        for j=1:height
            grayValue = grayImage(i,j);
            histNum(grayValue+1,1) = histNum(grayValue+1,1)+1; %该灰度的直方图取值+1
        end
    end
end