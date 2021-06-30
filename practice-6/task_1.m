clc;
clear;
close all;

srcImg = imread('images/lena.bmp');
imshow(srcImg); title('lenaԭͼ');

[width,height,bmgs]=size(srcImg); %���ͼ��ĳߴ磺��ȣ��߶�
oneDimen = reshape(srcImg,[],1); %%��Ϊһά����
figure;
hideImg = imread('images/911.bmp');
imshow(hideImg); title('�����ص���Ϣ');

hideOneDimen = reshape(hideImg,[],1); %%��Ϊһά����
[widthyy,bmgsyy]=size(hideOneDimen); %���ͼ��ĳߴ磺��ȣ��߶�

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

dstImg = reshape(oneDimen,width,height,bmgs);
figure;
imshow(dstImg);
title('����������Ϣ��lena');