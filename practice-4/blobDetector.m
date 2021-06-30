function labelArea = blobDetector(dstImage)
% 检测出dstImage中的每个连通区域（blob），并为每个blob贴上相同的标签；
% 最后根据每个标签计算出对应blob的面积，存到一个一维数组labelArea中。

[height,width,~]=size(dstImage);
label = 0;
for i=2:height
    for j=2:width
        % 如果当前像素为黑色
        if dstImage(i,j)==0
            % 如果该像素点的左上下面都没标签
            if ((dstImage(i,j-1)==0 || dstImage(i,j-1)==255) && ...
                (dstImage(i-1,j)==0 || dstImage(i-1,j)==255) && ...
                (dstImage(i,j+1)==0 || dstImage(i,j+1)==255) && ...
                (dstImage(i+1,j)==0 || dstImage(i+1,j)==255))
                % 则将标签数+1，并赋给该像素点
                label = label + 1;
                dstImage(i,j)=label;
                
            % 如果该像素点的左边有标签，则将此标签值赋给该像素点
            elseif (dstImage(i,j-1)~=0 && dstImage(i,j-1)~=255)
                dstImage(i,j) = dstImage(i,j-1);
                
            % 如果该像素点的上面有标签，则将此标签值赋给该像素点
            elseif (dstImage(i-1,j)~=0 && dstImage(i-1,j)~=255)
                dstImage(i,j) = dstImage(i-1,j);
                
            % 如果该像素点的右边有标签，则将此标签值赋给该像素点
            elseif (dstImage(i,j+1)~=0 && dstImage(i,j+1)~=255)
                dstImage(i,j) = dstImage(i,j+1);    
                
            % 如果该像素点的下面有标签，则将此标签值赋给该像素点
            elseif (dstImage(i+1,j)~=0 && dstImage(i+1,j)~=255)
                dstImage(i,j) = dstImage(i+1,j);
            end
        end
    end
end

for i=height:-1:2
    for j=width:-1:2
        % 如果该像素点有标签
        if (dstImage(i,j)~=0 && dstImage(i,j)~=255)
            
            % 如果该像素点的左边有标签，则将左边标签赋值给当前像素点
            if (dstImage(i,j-1)~=0 && dstImage(i,j-1)~=0)
                dstImage(i,j)=dstImage(i,j-1);
                
            % 如果该像素点的上边有标签，则将上边标签赋值给当前像素点
            elseif (dstImage(i-1,j)~=0 && dstImage(i-1,j)~=0)
                dstImage(i,j)=dstImage(i-1,j);
            
            % 如果该像素点的右边有标签，则将右边标签赋值给当前像素点
            elseif (dstImage(i,j+1)~=0 && dstImage(i,j+1)~=0)
                dstImage(i,j)=dstImage(i,j+1);
            % 如果该像素点的下边有标签，则将下边标签赋值给当前像素点
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