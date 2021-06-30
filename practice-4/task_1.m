%% 初始化
close all;
clear;
clc;

%% 加载图像"tixing.bmp"并进行图像预处理
srcImage = imread("images/tixing.bmp");
figure(1); imshow(srcImage); title("1 梯形原图");

% 转为灰度图
dstImage = rgb2gray(srcImage);
figure(2); imshow(dstImage); title("2 梯形灰度图");

% 阈值分割（转为二值图）
[height,width,~]=size(dstImage);

for i=1:height
    for j=1:width
        if dstImage(i,j)>60
            dstImage(i,j)=255;
        else
            dstImage(i,j)=0;
        end
    end
end

figure(3); imshow(dstImage); title("3 阈值分割效果图");
%% 检测blobs并计算其面积
labelArea = blobDetector(dstImage);

for i=1:size(labelArea,2)
    if labelArea(1,i)~=0
        fprintf("第%d个blob的面积为：%d\n",i,labelArea(1,i));
    end
end