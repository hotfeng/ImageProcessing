clc;
clear;
close all;

srcImg = imread('images/result.bmp');
imshow(srcImg);
title('附有隐藏信息的lena');
[width,height,bmgs]=size(srcImg); %获得图像的尺寸：宽度，高度

oneDimen = reshape(srcImg,[],1); %%变为一维矩阵
newValue = uint8(zeros(100*100,1));
for i=1:100*100
    %转换为字符串
    val_1 = dec2bin(0,8);
    s1=num2str(val_1); %转换为字符串
    
    for j=1:8
        val_2 = dec2bin(oneDimen(8*(i-1)+j),8);
        s2=num2str(val_2); %转换为字符串
        s1(j)=s2(8); %对最后一位取值
    end
    temp = bin2dec(s1);
    newValue(i,1) = temp;
end

dstImg = reshape(newValue,100,100,1);
figure;
imshow(dstImg);
title('隐藏的信息');