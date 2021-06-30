%% ��ʼ��
close all;
clear;
clc;

%% ����ͼ��"tixing.bmp"������ͼ��Ԥ����
srcImage = imread("images/tixing.bmp");
figure(1); imshow(srcImage); title("1 ����ԭͼ");

% תΪ�Ҷ�ͼ
dstImage = rgb2gray(srcImage);
figure(2); imshow(dstImage); title("2 ���λҶ�ͼ");

% ��ֵ�ָתΪ��ֵͼ��
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

figure(3); imshow(dstImage); title("3 ��ֵ�ָ�Ч��ͼ");
%% ���blobs�����������
labelArea = blobDetector(dstImage);

for i=1:size(labelArea,2)
    if labelArea(1,i)~=0
        fprintf("��%d��blob�����Ϊ��%d\n",i,labelArea(1,i));
    end
end