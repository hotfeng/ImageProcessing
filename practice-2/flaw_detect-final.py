import sys
import numpy as np
import cv2 as cv   
import time
from copy import deepcopy

# 腐蚀操作可以应用于消除噪声、分割一些独立的图像元素；而膨胀操作可以连接相邻的元素
# 膨胀的目的简单来讲可以理解为以输入的结构体为模板，对原图像中的非零部分的边缘进行扩展(例如填补空洞，形成联通区域)。
# 腐蚀则相反，对非零部分进行收缩(例如去掉小面积噪声)
# 腐蚀是消除物体的所有边界点的一个过程 膨胀是将与某物体接触的所有背景点合并到该物体中
# 膨胀与腐蚀能实现多种多样的功能，主要如下：

# 消除噪声
# 分割(isolate)出独立的图像元素，在图像中连接(join)相邻的元素。
# 寻找图像中的明显的极大值区域或极小值区域
# 求出图像的梯度

# 闭运算
# 在数学形态学中，闭运算被定义为先膨胀后腐蚀。
# 闭运算作用：经常被用来填充前景物体中的小洞，或者前景物体上的小黑点。

# 开运算
# 在数学形态学中，开运算被定义为先腐蚀后膨胀。
# 开运算作用：它被用来去除噪声

# 形态学梯度
# 其实就是一幅图像膨胀与腐蚀的之差。
# 形态学梯度作用：提取前景物体的轮廓。

# 礼帽操作
# 原始图像与进行开运算之后得到的图像的差。
# 形态学礼帽作用：提取图像中的噪声。

# 黑帽
# 进行闭运算之后得到的图像与原始图像的差。
# 形态学黑帽作用：突出噪声与原始图像的交界处，可近似表现出一些轮廓。

# 结构元素（Structure Element），在每个像素位置上与二值图像对应的区域进行特定的逻辑运算。
# 运算结构是输出图像的相应像素。运算效果取决于结构元素大小内容以及逻辑运算性质。
# 结构元素的原点指定了图像中需要处理的像素范围，结构元素中数值为1的点决定结构元素的领域像素进行膨胀或腐蚀操作时是否需要参与计算。
def main():
    cv.namedWindow('res', cv.WINDOW_NORMAL)
    cv.namedWindow('flaw', cv.WINDOW_NORMAL)
    cv.namedWindow('binary', cv.WINDOW_NORMAL)
    cv.namedWindow('gradient', cv.WINDOW_NORMAL)
    cv.namedWindow('op', cv.WINDOW_NORMAL)
    # cv.namedWindow('cnt', cv.WINDOW_NORMAL)
    input_img_path = 'images/flaw1.png'
    image = cv.imread(input_img_path)
    cv.imshow("flaw", image)
    initial_h, initial_w, __ = image.shape

    # kernel = cv.getStructuringElement(cv.MORPH_RECT, (6, 6))  # 矩形结构   
    kernel = cv.getStructuringElement(cv.MORPH_ELLIPSE, (6, 6))  # 椭圆结构   
    # dilation = cv.dilate(image, kernel)  # 膨胀
    # erosion = cv.erode(image, kernel)  # 腐蚀
    # gradient = cv.subtract(dilation, erosion)  #膨胀 - 腐蚀 = 形态梯度
    gradient = cv.morphologyEx(image, cv.MORPH_GRADIENT, kernel)  # 直接做形态梯度操作
    cv.imshow("gradient", gradient)
    lit = cv.convertScaleAbs(gradient, alpha=1.8, beta=0)# 对比度增强 线性变换
    
    # 灰度化 二值化
    gray = cv.cvtColor(lit, cv.COLOR_RGB2GRAY)
    binary = cv.threshold(
        gray, 0, 255,  cv.THRESH_OTSU)[1]
    cv.imshow("binary", binary)
	
    color_mask = np.array([0, 0, 255], dtype=np.uint8)
    binary_mask = binary.astype(np.bool)
    overlapping = deepcopy(image)
    overlapping[binary_mask] = overlapping[binary_mask] + color_mask * 0.2
    cv.imshow("op", overlapping)

    contours, hierarchy = cv.findContours(
        binary, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)
    # cv2.RETR_EXTERNAL表示只检测外轮廓
    # cv2.RETR_LIST检测的轮廓不建立等级关系
    # cv2.RETR_CCOMP建立两个等级的轮廓，上面的一层为外边界，里面的一层为内孔的边界信息。如果内孔内还有一个连通物体，这个物体的边界也在顶层。
    # cv2.RETR_TREE建立一个等级树结构的轮廓。
    # 第三个参数method为轮廓的近似办法
    # cv2.CHAIN_APPROX_NONE存储所有的轮廓点，相邻的两个点的像素位置差不超过1，即max（abs（x1-x2），abs（y2-y1））== 1
    # cv2.CHAIN_APPROX_SIMPLE压缩水平方向，垂直方向，对角线方向的元素，只保留该方向的终点坐标，例如一个矩形轮廓只需4个点来保存轮廓信息
    # cv2.CHAIN_APPROX_TC89_L1，CV_CHAIN_APPROX_TC89_KCOS使用teh-Chinl chain 近似算法
    # cv2.findContours()函数返回两个值，一个是轮廓本身，还有一个是每条轮廓对应的属性。
    
    # mask = np.zeros([image.shape[0], image.shape[1]], dtype=np.uint8)
    # cv.drawContours(mask, [contours[1]], 0, (255, 255, 255), 2)
    # cv.imshow("cnt", mask)

    id = 0
    for cnt in contours:
        area = cv.contourArea(cnt)
        Perimeter = cv.arcLength(cnt,True)
        rect = cv.boundingRect(cnt)  # x,y左上 w,h
        loc = (int(rect[0] + rect[2] / 2), int(rect[1] + rect[3] / 2))
        id = id+1
        overlapping = cv.rectangle(overlapping, (int(rect[0]),int(rect[1])),(int(rect[0]+rect[2]),int(rect[1]+rect[3])), (255,0,0),1) 
        print("ID:"+str(id)+" Area:"+str(int(area))+" Perimeter:"+str(int(Perimeter))+" Position:("+str(int(loc[0]))+","+str(int(loc[1]))+")") 
    cv.imshow("res", overlapping)

    cv.waitKey(0)


if __name__ == '__main__':
    main()

