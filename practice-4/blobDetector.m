function labelArea = blobDetector(dstImage)
% ����dstImage�е�ÿ����ͨ����blob������Ϊÿ��blob������ͬ�ı�ǩ��
% ������ÿ����ǩ�������Ӧblob��������浽һ��һά����labelArea�С�

[height,width,~]=size(dstImage);
label = 0;
for i=2:height
    for j=2:width
        % �����ǰ����Ϊ��ɫ
        if dstImage(i,j)==0
            % ��������ص���������涼û��ǩ
            if ((dstImage(i,j-1)==0 || dstImage(i,j-1)==255) && ...
                (dstImage(i-1,j)==0 || dstImage(i-1,j)==255) && ...
                (dstImage(i,j+1)==0 || dstImage(i,j+1)==255) && ...
                (dstImage(i+1,j)==0 || dstImage(i+1,j)==255))
                % �򽫱�ǩ��+1�������������ص�
                label = label + 1;
                dstImage(i,j)=label;
                
            % ��������ص������б�ǩ���򽫴˱�ǩֵ���������ص�
            elseif (dstImage(i,j-1)~=0 && dstImage(i,j-1)~=255)
                dstImage(i,j) = dstImage(i,j-1);
                
            % ��������ص�������б�ǩ���򽫴˱�ǩֵ���������ص�
            elseif (dstImage(i-1,j)~=0 && dstImage(i-1,j)~=255)
                dstImage(i,j) = dstImage(i-1,j);
                
            % ��������ص���ұ��б�ǩ���򽫴˱�ǩֵ���������ص�
            elseif (dstImage(i,j+1)~=0 && dstImage(i,j+1)~=255)
                dstImage(i,j) = dstImage(i,j+1);    
                
            % ��������ص�������б�ǩ���򽫴˱�ǩֵ���������ص�
            elseif (dstImage(i+1,j)~=0 && dstImage(i+1,j)~=255)
                dstImage(i,j) = dstImage(i+1,j);
            end
        end
    end
end

for i=height:-1:2
    for j=width:-1:2
        % ��������ص��б�ǩ
        if (dstImage(i,j)~=0 && dstImage(i,j)~=255)
            
            % ��������ص������б�ǩ������߱�ǩ��ֵ����ǰ���ص�
            if (dstImage(i,j-1)~=0 && dstImage(i,j-1)~=0)
                dstImage(i,j)=dstImage(i,j-1);
                
            % ��������ص���ϱ��б�ǩ�����ϱ߱�ǩ��ֵ����ǰ���ص�
            elseif (dstImage(i-1,j)~=0 && dstImage(i-1,j)~=0)
                dstImage(i,j)=dstImage(i-1,j);
            
            % ��������ص���ұ��б�ǩ�����ұ߱�ǩ��ֵ����ǰ���ص�
            elseif (dstImage(i,j+1)~=0 && dstImage(i,j+1)~=0)
                dstImage(i,j)=dstImage(i,j+1);
            % ��������ص���±��б�ǩ�����±߱�ǩ��ֵ����ǰ���ص�
            elseif (dstImage(i+1,j)~=0 && dstImage(i+1,1)~=0)
                dstImage(i,j)=dstImage(i+1,j);
            end
        end
        
    end
end

labelArea = zeros(1, 254);

for i=1:height
    for j=1:width
        if (dstImage(i,j)~=0 && dstImage(i,j)~=255)
            pixelVal = dstImage(i,j);
            labelArea(1,pixelVal) = labelArea(1,pixelVal) + 1;
        end
    end
end

end