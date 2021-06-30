%% 初始化
close all;
clear;
clc;

%% 读取“lenargb.bmp”与“guazi.bmp”
lenaImage = imread("images/lenargb.bmp");
gzImage = imread("images/guazi.bmp");

%% 使用matlab系统函数进行灰度化处理
% 对“lenargb.bmp”进行处理
lenaGray = rgb2gray(lenaImage);
figure(1);
subplot(121); imshow(lenaImage); title("1 lena原图");
subplot(122); imshow(lenaGray); title("2 lena灰度图(1)");

% 对“guazi.bmp”进行处理
gzGray = rgb2gray(gzImage);
figure(2);
subplot(121); imshow(gzImage); title("1 瓜子原图");
subplot(122); imshow(gzGray); title("2 瓜子灰度图(1)");

%% 自定义函数灰度化处理
gzGray2 = myGraying(gzImage);
lenaGray2 = myGraying(lenaImage);
figure(3);
subplot(121); imshow(gzGray2); title("3 瓜子灰度图(2)");
subplot(122); imshow(lenaGray2); title("3 lena灰度图(2)");

function grayImage = myGraying(srcImage)
    [width,height,~] = size(srcImage);
    grayImage =  uint8(zeros(width,height));
    for i = 1:width
        for j = 1:height
            grayImage(i,j) = srcImage(i,j,1)*0.299 + srcImage(i,j,2)*0.587 + srcImage(i,j,3) * 0.114;
        end
    end
end