%% 初始化
close all;
clear;
clc;

%% 读取原图并灰度化
srcImage = imread("images/rectangle_2.bmp");
grayImage = rgb2gray(srcImage);

%% 绘制直方图
figure(1);
subplot(121); imshow(srcImage); title("1 原图");
subplot(122); imhist(grayImage); title("2 直方图");

%% 阈值分割
[width,height,~] = size(grayImage);

for i = 1:width
    for j = 1:height
        if grayImage(i,j) > 120
            grayImage(i,j) = 255;
        else
            grayImage(i,j) = 0;
        end
    end
end

figure(2);
imshow(grayImage); title("阈值分割");

%% 计算blob面积
% 1.贴标签
labels = 0;

for i = 1:width
    for j = 1:height
        % 如果位置当前为黑色像素点
        if grayImage(i,j) == 0
            % 如果该像素点(i,j)的上下左右都没标签，则新建一个标签，并将该像素灰度值设为标签大小
            if ( ((grayImage(i,j-1)==0) || (grayImage(i,j-1)==255)) && ...
                 ((grayImage(i-1,j)==0) || (grayImage(i-1,j)==255)) && ...
                 ((grayImage(i,j+1)==0) || (grayImage(i,j+1)==255)) && ...
                 ((grayImage(i+1,j)==0) || (grayImage(i+1,j)==255)) )

                labels = labels + 1;
                grayImage(i,j) = labels;
            % 如果该像素点左边已有标签，则将该像素点灰度值设为与坐边像素点一致
            elseif ( (grayImage(i,j-1)~=0) && (grayImage(i,j-1)~=255) )
                grayImage(i,j) = grayImage(i,j-1);
            % 如果该像素点上边已有标签
            elseif ( (grayImage(i-1,j)~=0) && (grayImage(i-1,j)~=255) )
                grayImage(i,j) = grayImage(i-1,j);
            % 如果该像素点左边已有标签
            elseif ( (grayImage(i,j+1)~=0) && (grayImage(i,j+1)~=255) )
                grayImage(i,j) = grayImage(i,j+1);
            % 如果该像素点左边已有标签
            elseif ( (grayImage(i+1,j)~=0) && (grayImage(i+1,j)~=255) )
                grayImage(i,j) = grayImage(i+1,j);
            end
            
        end
    end
end

% 2.计算标签区域面积
labelArea = zeros(1, 254);
labelVal = 0;

for i=1:width
    for j = 1:height
        if( (grayImage(i,j)~=0) && (grayImage(i,j)~=255) )
            labelVal = grayImage(i,j);
            labelArea(1,labelVal) = labelArea(1,labelVal) + 1;
        end
            
    end
end

% 3.输出面积
for i = 1:size(labelArea,2)
    if labelArea(1,i) ~=0
        fprintf("第%d个blob的面积为：%d\n", i, labelArea(1,i));
    end
end