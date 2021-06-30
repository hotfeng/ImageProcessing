%% 初始化
close all;
clear;
clc;

%% 创建一个空白三维数组，遍历每一个像素值，并将r维数值设为255
Mat = zeros(100,100,3);
for i = 1:100
    for j = 1:100
        Mat(i,j,1) = 255;
    end
end

%% 显示空色图像并保存为.bmp文件
imshow(Mat);
imwrite(Mat,"images/red.bmp")