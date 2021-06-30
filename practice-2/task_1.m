%% ��ʼ��
close all;
clear;
clc;

%% ��ȡ��lenargb.bmp���롰guazi.bmp��
lenaImage = imread("images/lenargb.bmp");
gzImage = imread("images/guazi.bmp");

%% ʹ��matlabϵͳ�������лҶȻ�����
% �ԡ�lenargb.bmp�����д���
lenaGray = rgb2gray(lenaImage);
figure(1);
subplot(121); imshow(lenaImage); title("1 lenaԭͼ");
subplot(122); imshow(lenaGray); title("2 lena�Ҷ�ͼ(1)");

% �ԡ�guazi.bmp�����д���
gzGray = rgb2gray(gzImage);
figure(2);
subplot(121); imshow(gzImage); title("1 ����ԭͼ");
subplot(122); imshow(gzGray); title("2 ���ӻҶ�ͼ(1)");

%% �Զ��庯���ҶȻ�����
gzGray2 = myGraying(gzImage);
lenaGray2 = myGraying(lenaImage);
figure(3);
subplot(121); imshow(gzGray2); title("3 ���ӻҶ�ͼ(2)");
subplot(122); imshow(lenaGray2); title("3 lena�Ҷ�ͼ(2)");

function grayImage = myGraying(srcImage)
    [width,height,~] = size(srcImage);
    grayImage =  uint8(zeros(width,height));
    for i = 1:width
        for j = 1:height
            grayImage(i,j) = srcImage(i,j,1)*0.299 + srcImage(i,j,2)*0.587 + srcImage(i,j,3) * 0.114;
        end
    end
end