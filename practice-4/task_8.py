import cv2
import numpy as np
import matplotlib.pyplot as plt


"""
   图像的几何变换从原理上看主要包括两种：
   基于2×3矩阵的仿射变换（平移、缩放、旋转和翻转等）；基于3×3矩阵的透视变换
"""

# 读入原图
srcImage = cv2.imread("./images/lenargb.bmp", cv2.IMREAD_COLOR)
cv2.imshow("0 Source Image", srcImage)

"""
1. 仿射变换-旋转 cv::getRotationMatrix2D()

   retval = cv.getRotationMatrix2D(center, angle, scale)
   参数1：图片的旋转中心
   参数2：旋转角度(正：逆时针，负：顺时针)
   参数3：缩放比例，0.5表示缩小一半
"""
# 顺时针45°旋转图片并将其缩小一半
rows, cols = srcImage.shape[:2]

Matrix = cv2.getRotationMatrix2D((cols / 2, rows / 2), 45, 0.5)
rotateImage = cv2.warpAffine(srcImage, Matrix, (cols, rows))
cv2.imshow('1 Rotation', rotateImage)


"""
2. 仿射变换-平移 cv::warpAffine()

   dst = cv.warpAffine(src, M, dsize[, dst[, flags[, borderMode[, borderValue]]]])
"""
# 定义平移矩阵，需要是numpy的float32类型
# 向x轴方向右移100，向y轴方向上移50
Matrix = np.float32([[1, 0, 100], [0, 1, 50]])
# 用仿射变换实现平移
transImage = cv2.warpAffine(srcImage, Matrix, (cols, rows))
cv2.imshow("2 Translation", transImage)


"""
3. 仿射变换-缩放 cv2::resize()

   dst = cv.resize(src, dsize[, dst[, fx[, fy[, interpolation]]]])
   dsize：输出图像的尺寸。如果为None，则由此公式求得：dsize = Size(round(fx*src.cols), round(fy*src.rows))
"""
# 按照指定的宽度、高度缩放图片
zoomImage1 = cv2.resize(srcImage, (256, 256))
# 按照比例缩放，将x,y轴均放大1.5倍
zoomImage2 = cv2.resize(srcImage, None, fx=1.5, fy=1.5, interpolation = cv2.INTER_LINEAR)
cv2.imshow("3-1 Zoom in", zoomImage1), cv2.imshow("3-2 Zonm out", zoomImage2)


"""
4. 仿射变换-翻转 cv::flip()

   dst = cv.flip(src, flipCode[, dst])
   其中，参数flipCode = 0：垂直翻转(沿x轴)；参数flipCode > 0: 水平翻转(沿y轴)；参数flipCode < 0: 水平垂直翻转。
"""
dstImage = cv2.flip(srcImage, 1)
cv2.imshow("4 flip", dstImage)


"""
5. 透视变换：将图像从一个视平面投影到另外一个视平面的过程；
   透视变换的一般过程：读入图片，获取边界点，定义目标边界点，获取转换矩阵，执行转换；

   retval = cv.getPerspectiveTransform(src, dst[, solveMethod])
"""
warpImage = cv2.imread("images/warp.jpg")
warpImage = cv2.resize(warpImage, None, fx=0.6, fy=0.6)
cv2.imshow("5-1 Warp Image", warpImage)

# 源图像中四边形顶点的坐标
srcPoint = np.float32([[91, 171], [742,26], [18, 1135], [825, 1220]])
# 目标图像中相应的四边形顶点的坐标（左上、右上、左下、右下）
dstPoint = np.float32([[0, 0], [900, 0], [0, 1200], [900, 1200]])
# 生成透视变换矩阵
Matrix = cv2.getPerspectiveTransform(srcPoint, dstPoint)
# 进行透视变换
dstImage = cv2.warpPerspective(warpImage, Matrix, (960, 1280))
dstImage = cv2.resize(dstImage, None, fx=0.6, fy=0.6)
cv2.imshow("5-2 Perspective Transformation", dstImage)


cv2.waitKey(0)