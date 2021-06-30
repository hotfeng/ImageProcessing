%% ��ʼ��
close all;
clear;
clc;

%% ��ȡ��lenargb.bmp���롰guazi.bmp�����ҶȻ�
lenaImage = imread("images/lenargb.bmp");
lenaGray = rgb2gray(lenaImage);

gzImage = imread("images/guazi.bmp");
gzGray = rgb2gray(gzImage);

%% ʹ��matlab������ȡֱ��ͼ��Ϣ
figure(1)
subplot(121); imshow(lenaGray); title("1 lena�Ҷ�ͼ");
subplot(122); imhist(lenaGray); title("2 lenaֱ��ͼ");

figure(2);
subplot(121); imshow(gzGray); title("1 ���ӻҶ�ͼ");
subplot(122); imhist(gzGray); title("2 ����ֱ��ͼ");

%% ʹ���Զ��庯����ȡֱ��ͼ��Ϣ
lenaHist = myHist(lenaGray);
gzHist = myHist(gzGray);
figure(3);
subplot(121); plot(lenaHist); title("1 lenaֱ��ͼ")
subplot(122); plot(gzHist); title("2 ����ֱ��ͼ")


function histNum = myHist(grayImage)
    [width,height,~] = size(grayImage);
    histNum = zeros(256,1); %ֱ��ͼ����
    for i=1:width
        for j=1:height
            grayValue = grayImage(i,j);
            histNum(grayValue+1,1) = histNum(grayValue+1,1)+1; %�ûҶȵ�ֱ��ͼȡֵ+1
        end
    end
end