import cv2
img = cv2.imread("./images/orange.jpg")

if img is None:
    print("Cannot load this image!")
# 获取像素点值(3通道/单通道); img[y, x]
pixel = img[100, 100]
print("The pixel of [100,100]:", pixel)
pixel_red = img[100, 100, 2]
print("The pixel of [100,100, 2]:", pixel_red)

# 修改像素点值
img[100, 100] = [255, 255, 255]

# 获取图像形状
print("The shape of img:", img.shape)
width, height, chennels = img.shape

# 获取图像数据类型
print("The data type of img:", img.dtype)

# 获取图像总像素点
print("The total number of pixel:", img.size)

# 获取ROI
ROI = img[245:480, 395:635]
cv2.imshow("source image", img)
cv2.imshow("Region of interst", ROI)

cv2.waitKey(0)
