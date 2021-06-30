%% 初始化
close all;
clear;
clc;

%% 读取原图并灰度化处理
srcImage = imread("images/square-noise.bmp");
figure(1); imshow(srcImage); title("1 方块噪声原图");
grayImage = rgb2gray(srcImage);
figure(2); imshow(grayImage); title("2 方块噪声灰度图");

%% 高斯滤波
gaussFiltImage = imgaussfilt(grayImage,0.5);    %0.5：高斯核函数的标准差
figure(3); imshow(gaussFiltImage); title("3 方块-高斯滤波效果图");

%% 计算直方图 & 阈值分割
figure(4); imhist(gaussFiltImage); title("4 方块直方图（高斯滤波后）");

[height,width,~] = size(gaussFiltImage);
for i=1:height
    for j=1:width
        if (gaussFiltImage(i,j) > 60)
            gaussFiltImage(i,j) = 255;
        else
            gaussFiltImage(i,j) = 0;
        end
    end
end
figure(5); imshow(gaussFiltImage); title("5 方块-阈值分割效果图");

%% 检测blobs并计算其面积
labelArea = blobDetector(gaussFiltImage);

for i=1:size(labelArea,2)
    if labelArea(1,i)~=0
        fprintf("第%d个blob的面积为：%d\n",i,labelArea(1,i));
    end
end