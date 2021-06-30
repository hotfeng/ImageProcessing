%% ��ʼ��
close all;
clear;
clc;

%% �򿪡�lenargb.bmp���͡�guazi.bmp�������лҶȻ�
lenaImage = imread("images/lenargb.bmp");
gzImage = imread("images/guazi.bmp");

lenaGray = rgb2gray(lenaImage);
gzGray = rgb2gray(gzImage);

figure(1);
subplot(221); imshow(lenaImage); title("1 lenaԭͼ");
subplot(222); imshow(lenaGray); title("2 lena�Ҷ�ͼ");
subplot(223); imshow(gzImage); title("3 ����ԭͼ");
subplot(224); imshow(gzGray); title("4 ���ӻҶ�ͼ");

%% ���㲢����ֱ��ͼ
figure(2);
subplot(121); imhist(lenaGray); title("1 lenaֱ��ͼ");
subplot(122); imhist(gzGray); title("2 ����ֱ��ͼ");

%% ��ֵ�ָ�
thresholdImage = threshold(lenaGray);
figure(3);
imshow(thresholdImage); title("��ֵ�ָ�Ч��ͼ-lena");

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