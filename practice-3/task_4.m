%% ��ʼ��
close all;
clear;
clc;

%% ��ȡԭͼ���ҶȻ�
srcImage = imread("images/rectangle_2.bmp");
grayImage = rgb2gray(srcImage);

%% ����ֱ��ͼ
figure(1);
subplot(121); imshow(srcImage); title("1 ԭͼ");
subplot(122); imhist(grayImage); title("2 ֱ��ͼ");

%% ��ֵ�ָ�
[width,height,~] = size(grayImage);

for i = 1:width
    for j = 1:height
        if grayImage(i,j) > 120
            grayImage(i,j) = 255;
        else
            grayImage(i,j) = 0;
        end
    end
end

figure(2);
imshow(grayImage); title("��ֵ�ָ�");

%% ����blob���
% 1.����ǩ
labels = 0;

for i = 1:width
    for j = 1:height
        % ���λ�õ�ǰΪ��ɫ���ص�
        if grayImage(i,j) == 0
            % ��������ص�(i,j)���������Ҷ�û��ǩ�����½�һ����ǩ�����������ػҶ�ֵ��Ϊ��ǩ��С
            if ( ((grayImage(i,j-1)==0) || (grayImage(i,j-1)==255)) && ...
                 ((grayImage(i-1,j)==0) || (grayImage(i-1,j)==255)) && ...
                 ((grayImage(i,j+1)==0) || (grayImage(i,j+1)==255)) && ...
                 ((grayImage(i+1,j)==0) || (grayImage(i+1,j)==255)) )

                labels = labels + 1;
                grayImage(i,j) = labels;
            % ��������ص�������б�ǩ���򽫸����ص�Ҷ�ֵ��Ϊ���������ص�һ��
            elseif ( (grayImage(i,j-1)~=0) && (grayImage(i,j-1)~=255) )
                grayImage(i,j) = grayImage(i,j-1);
            % ��������ص��ϱ����б�ǩ
            elseif ( (grayImage(i-1,j)~=0) && (grayImage(i-1,j)~=255) )
                grayImage(i,j) = grayImage(i-1,j);
            % ��������ص�������б�ǩ
            elseif ( (grayImage(i,j+1)~=0) && (grayImage(i,j+1)~=255) )
                grayImage(i,j) = grayImage(i,j+1);
            % ��������ص�������б�ǩ
            elseif ( (grayImage(i+1,j)~=0) && (grayImage(i+1,j)~=255) )
                grayImage(i,j) = grayImage(i+1,j);
            end
            
        end
    end
end

% 2.�����ǩ�������
labelArea = zeros(1, 254);
labelVal = 0;

for i=1:width
    for j = 1:height
        if( (grayImage(i,j)~=0) && (grayImage(i,j)~=255) )
            labelVal = grayImage(i,j);
            labelArea(1,labelVal) = labelArea(1,labelVal) + 1;
        end
            
    end
end

% 3.������
for i = 1:size(labelArea,2)
    if labelArea(1,i) ~=0
        fprintf("��%d��blob�����Ϊ��%d\n", i, labelArea(1,i));
    end
end