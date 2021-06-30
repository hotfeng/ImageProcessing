#引入opencv模块
import cv2 as cv
#引入numpy模块
import numpy as np
#引入sys模块
import sys


#自动阈值分割方法1 OTSU，根据灰度统计
def threshold_otsu(img):
    gray = cv.cvtColor(img,cv.COLOR_BGR2GRAY)
    ret, binary = cv.threshold(gray,0,255,cv.THRESH_BINARY|cv.THRESH_OTSU)
    print("threshold_otsu %s"%(ret))
    return binary


#自动阈值分割方法2 TRIANGLE，根据灰度统计
def threshold_triangle(img):
    gray = cv.cvtColor(img,cv.COLOR_BGR2GRAY)
    ret, binary = cv.threshold(gray,0,255,cv.THRESH_BINARY|cv.THRESH_TRIANGLE)
    print("threshold_otsu %s"%(ret))
    return binary


#手动指定阈值的分割方法，自己设定阈值th_val
#注意，此时，不指定自动方法
def threshold_manualset(img,th_val):
    gray = cv.cvtColor(img,cv.COLOR_BGR2GRAY)
    ret, binary = cv.threshold(gray,th_val,255,cv.THRESH_BINARY)
    #(1)注意，下面的方法是反色的分割，黑白颠倒过来，可以试下
    #ret, binary = cv.threshold(gray,th_val,255,cv.THRESH_BINARY_INV)  
    #(2)注意，下面的方法是截断的阈值分割，小于th_val的都赋值th_val，可以试下 
    #ret, binary = cv.threshold(gray,th_val,255,cv.THRESH_TRUNC)   
     #(3)注意，下面的方法是截断清零的阈值分割，小于th_val的都赋值0，可以试下 
    #ret, binary = cv.threshold(gray,th_val,255,cv.THRESH_TOZERO)   
    #ret, binary = cv.threshold(gray,th_val,255,cv.THRESH_TOZERO_INV)   

    print("threshold_otsu %s"%(ret))
    return binary


#自动局部自适应阈值分割方法1，MEAN方法
def threshold_local_mean(img):
    gray = cv.cvtColor(img,cv.COLOR_BGR2GRAY)
    #block size参数，这里设为25的必须为奇数，自己可以改
    #C为常数，也就是计算结果进行处理的阈值，自己可以改
    binary = cv.adaptiveThreshold(gray,255,cv.ADAPTIVE_THRESH_MEAN_C,cv.THRESH_BINARY,25,10)
    return binary


#自动局部自适应阈值分割方法2，GAUSSIAN方法
def threshold_local_guassian(img):
    gray = cv.cvtColor(img,cv.COLOR_BGR2GRAY)
    #block size参数，这里设为25的必须为奇数，自己可以改
    #C为常数，也就是计算结果进行处理的阈值，自己可以改
    binary = cv.adaptiveThreshold(gray,255,cv.ADAPTIVE_THRESH_GAUSSIAN_C,cv.THRESH_BINARY,25,10)
    return binary


#自己根据图像的均值，傻瓜计算
def threshold_custom(img):
    gray = cv.cvtColor(img,cv.COLOR_BGR2GRAY)
    h,w = gray.shape[:2]
    m = np.reshape(gray,[1,w*h])
    mean = m.sum()/(w*h)
    print("mean: %s"%(mean))
    ret, binary = cv.threshold(gray,mean,255,cv.THRESH_BINARY)
    print("threshold_otsu %s"%(ret))    
    return binary


def img_test():
    #img = cv.imread('E:/chenopencvblogimg/lena.jpg')
    img = cv.imread('images/lena.bmp')
    #判断是否读取成功
    if img is None:
        print("Could not read the image,may be path error")
        return
    cv.namedWindow("origin Pic",cv.WINDOW_NORMAL)
    cv.imshow("origin Pic",img)

    img_show = threshold_otsu(img) 
    cv.namedWindow("threshold_otsu",cv.WINDOW_NORMAL)
    cv.imshow("threshold_otsu",img_show)

    img_show = threshold_triangle(img) 
    cv.namedWindow("threshold_triangle",cv.WINDOW_NORMAL)
    cv.imshow("threshold_triangle",img_show)

    img_show = threshold_manualset(img,127) 
    cv.namedWindow("threshold_manualset",cv.WINDOW_NORMAL)
    cv.imshow("threshold_manualset",img_show)

    img_show = threshold_local_mean(img) 
    cv.namedWindow("threshold_local_mean",cv.WINDOW_NORMAL)
    cv.imshow("threshold_local_mean",img_show)

    img_show = threshold_local_guassian(img) 
    cv.namedWindow("threshold_local_guassian",cv.WINDOW_NORMAL)
    cv.imshow("threshold_local_guassian",img_show)


    img_show = threshold_custom(img) 
    cv.namedWindow("threshold_custom",cv.WINDOW_NORMAL)
    cv.imshow("threshold_custom",img_show)

    #让显示等待键盘输入维持在那里，否则程序跑完就闪退啦！
    cv.waitKey(0)
    #销毁窗口
    cv.destroyAllWindows()

if __name__ == '__main__':
    sys.exit(img_test() or 0)