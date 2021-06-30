import cv2

img = cv2.imread('images/handwriting.png')
img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
# 使用Otsu自动阈值
ret, thresh = cv2.threshold(
    img_gray, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)

# 寻找轮廓
contours, hierarchy = cv2.findContours(
    thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

# 绘制轮廓
cv2.drawContours(img, contours, -1, (0, 0, 255), 2)

cv2.imshow('contours', img)
cv2.waitKey(0)
