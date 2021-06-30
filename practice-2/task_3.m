%% 初始化
close all;
clear;
clc;

%% 打开“lenargb.bmp”和“guazi.bmp”并进行灰度化
lenaImage = imread("images/lenargb.bmp");
gzImage = imread("images/guazi.bmp");

lenaGray = rgb2gray(lenaImage);
gzGray = rgb2gray(gzImage);

figure(1);
subplot(221); imshow(lenaImage); title("1 lena原图");
subplot(222); imshow(lenaGray); title("2 lena灰度图");
subplot(223); imshow(gzImage); title("3 瓜子原图");
subplot(224); imshow(gzGray); title("4 瓜子灰度图");

%% 计算并绘制直方图
figure(2);
subplot(121); imhist(lenaGray); title("1 lena直方图");
subplot(122); imhist(gzGray); title("2 瓜子直方图");

%% 阈值分割
thresholdImage = threshold(lenaGray);
figure(3);
imshow(thresholdImage); title("阈值分割效果图-lena");

function grayImage = threshold(grayImage)
    [width,height,~] = size(grayImage);
    for i=1:width
        for j = 1:height
            if grayImage(i,j) > 128
                grayImage(i,j) = 255;
            else
                grayImage(i,j) = 0;
            end
            
        end
    end
end