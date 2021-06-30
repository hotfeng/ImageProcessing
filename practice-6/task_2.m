clc;
clear;
close all;

srcImg = imread('images/result.bmp');
imshow(srcImg);
title('����������Ϣ��lena');
[width,height,bmgs]=size(srcImg); %���ͼ��ĳߴ磺��ȣ��߶�

oneDimen = reshape(srcImg,[],1); %%��Ϊһά����
newValue = uint8(zeros(100*100,1));
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
    newValue(i,1) = temp;
end

dstImg = reshape(newValue,100,100,1);
figure;
imshow(dstImg);
title('���ص���Ϣ');