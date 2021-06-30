import cv2
import numpy as np

# 获取蓝色HSV值
blue = np.uint8([[[0, 0, 255]]])
hsv_blue = cv2.cvtColor(blue, cv2.COLOR_BGR2HSV)
print(hsv_blue)     # [[[  0 255 255]]]

# 定义蓝色hsv值上下限
lower_blue = np.array([100, 110, 110])
upper_blue = np.array([130, 255, 255])

cap = cv2.VideoCapture(0)

while (cap.isOpened()):
    # 获取摄像头中当前帧并转为hsv格式
    ret, frame = cap.read()
    frame = cv2.resize(frame, (0, 0), fx=0.4, fy=0.4)
    hsvImg = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # 获取图像掩膜
    Mask = cv2.inRange(hsvImg, lower_blue, upper_blue)

    # 将原图frame与掩膜Mask做二进制"与"操作
    dstImage = cv2.bitwise_and(frame, frame, mask=Mask)

    # 显示原图，掩膜，合并图
    cv2.imshow("[Source Image]", frame)
    cv2.imshow("[Mask]", Mask)
    cv2.imshow("[Result(Recognize blue)]", dstImage)

    # 按‘q’键退出
    if cv2.waitKey(30) == ord('q'):
        break
