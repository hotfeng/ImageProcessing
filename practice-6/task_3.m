%% 初始化
clc;
clear;
close all;

%% 加载原图及信息图
srcImg = imread('images/lena.bmp');
imshow(srcImg); title('lena原图');

figure;
hideImg = imread('images/Axinxi.jpg');
imshow(hideImg); title('待隐藏的信息');

%% 开始隐藏信息
dstHideImg = InfoHide(srcImg, hideImg);
figure;
imshow(dstHideImg);
title('附有隐藏信息的lena');

%% 开始提取信息
dstExtractImg = InfoExtract(dstHideImg);
figure;
imshow(dstExtractImg);
title("提取到的信息");


%% 信息隐藏函数
function dstHideImg = InfoHide(srcImg, hideImg)
    [width,height,bmgs]=size(srcImg); %获得图像的尺寸：宽度，高度
    oneDimen = reshape(srcImg,[],1); %%变为一维矩阵

    hideOneDimen = reshape(hideImg,[],1); %%变为一维矩阵
    [widthyy,~]=size(hideOneDimen); %获得图像的尺寸：宽度，高度

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
    dstHideImg = reshape(oneDimen,width,height,bmgs);
end

%% 信息提取函数
function dstExtractImg = InfoExtract(srcImg)
    oneDimen = reshape(srcImg,[],1); %%变为一维矩阵
    tempImg = uint8(zeros(100*100,1));
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
        tempImg(i,1) = temp;
    end
    dstExtractImg = reshape(tempImg,100,100,1);
end
