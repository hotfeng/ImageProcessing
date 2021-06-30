%% 初始化
close all;
clear;
clc;

%% 分别加载三幅图像
img_path = dir(strcat("images/",'tu*.jpg'));   %依次仅读取文件夹中的tu1.jpg、tu2.jpg、tu3.jpg

for i=1:3
    picture_name = img_path(i).name;           %获取图片的名称
    srcImg = imread(strcat("images/",picture_name));          %建立循环函数依次读取原始图像
    figure;
    imshow(srcImg);
    title(picture_name);
    
    % 调用自定义函数判断图像颜色
    colorDetection(picture_name,srcImg);
end
%% 定义专门用来检测图像颜色的函数detection_color，接收两个实参（图片名，image对象）
function colorDetection(picture_name,img)
red=0;
yellow=0;
green=0;

% 通过计算像素值判断颜色
% szdim = size(A,dim) 返回维度 dim 的长度。
for i = 1:size(img,1)
        for j = 1:size(img,2)
            if img(i,j,1)>=200 && img(i,j,2)<=50 && img(i,j,3)<=50
                red=red+1;
            elseif img(i,j,1)>=200 && img(i,j,2)>=200 && img(i,j,3)<=50
                yellow=yellow+1;
            elseif img(i,j,2)>=200 && img(i,j,1)<=100 && img(i,j,3)<=100
                green=green+1;
            end
        end
end

% 通过比较RGB三种色素判断最终颜色
if max(max(red,yellow),green)==red
        color = 'red';
elseif max(max(red,yellow),green)==yellow
        color = 'yellow';
elseif max(max(red,yellow),green)==green
        color = 'green';
end

fprintf("The color of '%s' is %s.\n",picture_name,color)
end