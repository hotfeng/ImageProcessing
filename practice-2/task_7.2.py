import cv2


srcImage = cv2.imread(
    r"images\orange.jpg")
cv2.namedWindow("Canny")


def nothing(x):
    # define callback function
    pass


# 创建两个滑动条，分别调整Canny边缘检测中的高低阈值
cv2.createTrackbar("max", "Canny", 0, 255, nothing)
cv2.createTrackbar("min", "Canny", 50, 255, nothing)

while (True):
    # 获取滑动条当前位置
    maxVal = cv2.getTrackbarPos("max", "Canny")
    minVal = cv2.getTrackbarPos("min", "Canny")

    # 对原始图像进行Canny边缘检测并显示
    dstImage = cv2.Canny(srcImage, minVal, maxVal)
    cv2.imshow("Canny", dstImage)
    if cv2.waitKey(1) == ord('q'):
        break

cv2.destroyAllWindows()
