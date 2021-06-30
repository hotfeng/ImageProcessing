import cv2

capture = cv2.VideoCapture(0)
fourcc = cv2.VideoWriter_fourcc(*'MJPG')    # 设置视频编码格式
outfile = cv2.VideoWriter("record.avi", fourcc, 25, (640, 480))

while(capture.isOpened()):
    ret, frame = capture.read()
    grayImage = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)     # 灰度化
    edgesImage = cv2.blur(grayImage, (7, 7))                # 均值滤波
    edgesImage = cv2.Canny(edgesImage, 3, 9, 3)             # Canny边缘检测

    outfile.write(edgesImage)
    cv2.imshow("ME", edgesImage)
    if cv2.waitKey(30) == ord('q'):
        break
