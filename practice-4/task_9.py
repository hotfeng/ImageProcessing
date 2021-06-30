import cv2
import numpy as np
import matplotlib.pyplot as plt


# 创建一副三通道黑色图片（512*521*3）
img = np.zeros((512, 512, 3), np.uint8)


"""
1.  画直线：需指定起点和终点坐标 cv::line()

    img = cv.line(img, pt1, pt2, color[, thickness[, lineType[, shift]]])
"""
# 画一条线宽为5的蓝色直线。起点坐标：(0,0)，终点坐标：(512,512)
cv2.line(img, (0, 0), (512, 512), (255, 0, 0), 5)


"""
2.  画矩形：需指定左上角和右下角的坐标 cv::rectangle()

    img = cv.rectangle(img, pt1, pt2, color[, thickness[, lineType[, shift]]])
"""
# 以指定边界点画一个绿色矩形，线宽为2
cv2.rectangle(img, (384, 0), (510, 128), (0, 255, 0), 2)


"""
3.  画圆：需要指定圆心和半径 cv::circle()

    img = cv.circle(img, center, radius, color[, thickness[, lineType[, shift]]])
    注：thichness=-1表示以指定颜色填充此圆形
"""
# 画一个填充红色的圆，参数2：圆心坐标，参数3：半径
cv2.circle(img, (447, 63), 63, (0, 0, 255), -1)

"""
4.  画多边形：需要指定多边形一系列顶点坐标，相当于从第一个点到第二个点画直线，再从第二个点到第三个点画直线....
    OpenCV中需要先将多边形的顶点坐标需要变成 （顶点数*1*2） 维的矩阵，再来绘制

    img = cv.polylines(img, pts, isClosed, color[, thickness[, lineType[, shift]]])
"""
# 定义五个顶点坐标
pts = np.array([[45, 360],  [100, 316], [154, 360], [133, 430], [67, 430]], np.int32)
# 顶点个数：4，矩阵变成5*1*2维
pts = pts.reshape((-1, 1, 2), order='C')   # 第一个参数中的-1指的是：Numpy会根据剩下的维度计算出数组的此shape属性值
cv2.polylines(img, [pts], True, (0, 255, 255), 2)


"""
5.  添加文字：putText()

    img = cv.putText(img, text, org, fontFace, fontScale, color[, thickness[, lineType[, bottomLeftOrigin]]])
    text：要添加的文本
    org：文字的起始坐标（左下角为起点）
    fontFace：字体类型
    fontScale：文字大小（缩放比例）
    lineType：线型，cv::LINE_AA表示锯齿形
"""
# 设置字体格式
font = cv2.FONT_HERSHEY_SIMPLEX
cv2.putText(img, "Test for cv2.putText()", (10, 500), font, 1, (255, 255, 255), 2, lineType=cv2.LINE_AA)


cv2.namedWindow("Plot Exercise", cv2.WINDOW_AUTOSIZE)
cv2.imshow("Plot Exercise", img)

cv2.waitKey(0)