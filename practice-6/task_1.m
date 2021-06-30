clc;
clear;
close all;

srcImg = imread('images/lena.bmp');
imshow(srcImg); title('lena原图');

[width,height,bmgs]=size(srcImg); %获得图像的尺寸：宽度，高度
oneDimen = reshape(srcImg,[],1); %%变为一维矩阵
figure;
hideImg = imread('images/911.bmp');
imshow(hideImg); title('待隐藏的信息');

hideOneDimen = reshape(hideImg,[],1); %%变为一维矩阵
[widthyy,bmgsyy]=size(hideOneDimen); %获得图像的尺寸：宽度，高度

for i=1:widthyy
    value=dec2bin(hideOneDimen(i),8); %%转换为8 位二进制
    s1=num2str(value); %转换为字符串,待隐藏信息
    for j=1:8
        value_2 = dec2bin(oneDimen(8*(i-1)+j),8); %%载体
        s2=num2str(value_2); %转换为字符串
        s2(8)=s1(9-j); %对最后一位赋值
        temp = bin2dec(s2);
        oneDimen(8*(i-1)+j) = temp;
    end
end

dstImg = reshape(oneDimen,width,height,bmgs);
figure;
imshow(dstImg);
title('附有隐藏信息的lena');