%% ��ʼ��
close all;
clear;
clc;

%% ��ȡԭͼ���ҶȻ�����
srcImage = imread("images/square-noise.bmp");
figure(1); imshow(srcImage); title("1 ��������ԭͼ");
grayImage = rgb2gray(srcImage);
figure(2); imshow(grayImage); title("2 ���������Ҷ�ͼ");

%% ��˹�˲�
gaussFiltImage = imgaussfilt(grayImage,0.5);    %0.5����˹�˺����ı�׼��
figure(3); imshow(gaussFiltImage); title("3 ����-��˹�˲�Ч��ͼ");

%% ����ֱ��ͼ & ��ֵ�ָ�
figure(4); imhist(gaussFiltImage); title("4 ����ֱ��ͼ����˹�˲���");

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
figure(5); imshow(gaussFiltImage); title("5 ����-��ֵ�ָ�Ч��ͼ");

%% ���blobs�����������
labelArea = blobDetector(gaussFiltImage);

for i=1:size(labelArea,2)
    if labelArea(1,i)~=0
        fprintf("��%d��blob�����Ϊ��%d\n",i,labelArea(1,i));
    end
end