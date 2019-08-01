from skimage import io
import matplotlib.pyplot as plt
import numpy as np
from PIL import Image
import cv2
import sys

"""
Python Image Processing lib 
1. opencv
2. PIL
3. matplotlib 
4. skimage 

type of image object: 
opencv,matplotlib,skimage: numpy's ndarray
PIL: own image class

"""


############################
# opencv
###########################
img = cv2.imread('./test.jpg')
if img == None:
    print('This file may not be available')
    sys.exit()
print('image type', type(img))
print('image shape: ', img.shape)
cv2.imshow('image test', img)
cv2.waitKey()  # call waitKey after imshow to show image
cv2.imwrite('new_image.jpg', img)


############################
# PIL
###########################


img = Image.open('./test.jpg')
img.show()
img_arr = np.array(img)
new_img = Image.fromarray(img_arr)
new_img.save('newimage.jpg')

# convert to gray image
gary = Image.open('./test.jpg').convert('L')

r, g, b = img.split()
r == img.getchannel(0)
img = Image.merge('RGB', (r, g, b))
# copy image
img_copy = img.copy()

roi = img.crop((200, 300, 400, 500))

img_resize = img.resize((h, w))
# 旋转
img_r90 = img.rotate(90)  # 旋转90度
img_transpose_tb = img.transpose(Image.FLIP_TOP_BOTTOM)  # 上下翻转
img_transpose_lr = img.transpose(Image.FLIP_LEFT_RIGHT)  # 左右翻


############################
# matplotlib.pyplot
###########################

img = plt.imread('test.jpg')  # 可以读取tif文件
plt.imshow(img)
plt.axis('off')  # 关闭坐标轴上的数字
plt.show()
plt.savefig('new_img.jpg')


############################
# skimage
###########################

img = io.imread('test.jpg')
io.imshow(img)
io.show()
io.imsave('new_img.jpg', img)
