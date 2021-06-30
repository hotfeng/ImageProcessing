import cv2 as cv
import matplotlib.pyplot as plt


srcImg = cv.imread("images/lenargb.bmp", 1)

"""转换图像通道(BGR to RGB)"""
dstImg = cv.cvtColor(srcImg, cv.COLOR_BGR2RGB)

"""通过matplotlib显示原图/彩色图"""
plt.figure("lena")

plt.subplot(121), plt.imshow(srcImg)
plt.subplot(122), plt.imshow(dstImg)

plt.show()
