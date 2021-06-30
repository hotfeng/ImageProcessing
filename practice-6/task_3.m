%% ��ʼ��
clc;
clear;
close all;

%% ����ԭͼ����Ϣͼ
srcImg = imread('images/lena.bmp');
imshow(srcImg); title('lenaԭͼ');

figure;
hideImg = imread('images/Axinxi.jpg');
imshow(hideImg); title('�����ص���Ϣ');

%% ��ʼ������Ϣ
dstHideImg = InfoHide(srcImg, hideImg);
figure;
imshow(dstHideImg);
title('����������Ϣ��lena');

%% ��ʼ��ȡ��Ϣ
dstExtractImg = InfoExtract(dstHideImg);
figure;
imshow(dstExtractImg);
title("��ȡ������Ϣ");


%% ��Ϣ���غ���
function dstHideImg = InfoHide(srcImg, hideImg)
    [width,height,bmgs]=size(srcImg); %���ͼ��ĳߴ磺��ȣ��߶�
    oneDimen = reshape(srcImg,[],1); %%��Ϊһά����

    hideOneDimen = reshape(hideImg,[],1); %%��Ϊһά����
    [widthyy,~]=size(hideOneDimen); %���ͼ��ĳߴ磺��ȣ��߶�

    for i=1:widthyy
        value=dec2bin(hideOneDimen(i),8); %%ת��Ϊ8 λ������
        s1=num2str(value); %ת��Ϊ�ַ���,��������Ϣ
        for j=1:8
            value_2 = dec2bin(oneDimen(8*(i-1)+j),8); %%����
            s2=num2str(value_2); %ת��Ϊ�ַ���
            s2(8)=s1(9-j); %�����һλ��ֵ
            temp = bin2dec(s2);
            oneDimen(8*(i-1)+j) = temp;
        end
    end
    dstHideImg = reshape(oneDimen,width,height,bmgs);
end

%% ��Ϣ��ȡ����
function dstExtractImg = InfoExtract(srcImg)
    oneDimen = reshape(srcImg,[],1); %%��Ϊһά����
    tempImg = uint8(zeros(100*100,1));
    for i=1:100*100
        %ת��Ϊ�ַ���
        val_1 = dec2bin(0,8);
        s1=num2str(val_1); %ת��Ϊ�ַ���

        for j=1:8
            val_2 = dec2bin(oneDimen(8*(i-1)+j),8);
            s2=num2str(val_2); %ת��Ϊ�ַ���
            s1(j)=s2(8); %�����һλȡֵ
        end
        temp = bin2dec(s1);
        tempImg(i,1) = temp;
    end
    dstExtractImg = reshape(tempImg,100,100,1);
end
