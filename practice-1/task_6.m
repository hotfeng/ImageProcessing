%% ��ʼ��
close all;
clear;
clc;

%% �ֱ��������ͼ��
img_path = dir(strcat("images/",'tu*.jpg'));   %���ν���ȡ�ļ����е�tu1.jpg��tu2.jpg��tu3.jpg

for i=1:3
    picture_name = img_path(i).name;           %��ȡͼƬ������
    srcImg = imread(strcat("images/",picture_name));          %����ѭ���������ζ�ȡԭʼͼ��
    figure;
    imshow(srcImg);
    title(picture_name);
    
    % �����Զ��庯���ж�ͼ����ɫ
    colorDetection(picture_name,srcImg);
end
%% ����ר���������ͼ����ɫ�ĺ���detection_color����������ʵ�Σ�ͼƬ����image����
function colorDetection(picture_name,img)
red=0;
yellow=0;
green=0;

% ͨ����������ֵ�ж���ɫ
% szdim = size(A,dim) ����ά�� dim �ĳ��ȡ�
for i = 1:size(img,1)
        for j = 1:size(img,2)
            if img(i,j,1)>=200 && img(i,j,2)<=50 && img(i,j,3)<=50
                red=red+1;
            elseif img(i,j,1)>=200 && img(i,j,2)>=200 && img(i,j,3)<=50
                yellow=yellow+1;
            elseif img(i,j,2)>=200 && img(i,j,1)<=100 && img(i,j,3)<=100
                green=green+1;
            end
        end
end

% ͨ���Ƚ�RGB����ɫ���ж�������ɫ
if max(max(red,yellow),green)==red
        color = 'red';
elseif max(max(red,yellow),green)==yellow
        color = 'yellow';
elseif max(max(red,yellow),green)==green
        color = 'green';
end

fprintf("The color of '%s' is %s.\n",picture_name,color)
end