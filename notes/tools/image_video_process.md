
# imagemagick

ImageMagick[官网](https://www.imagemagick.org): 是一款创建、编辑、合成，转换图像的命令行工具。支持格式超过 200 种，包括常见的 PNG, JPEG, GIF, HEIC, TIFF, DPX, EXR, WebP, Postscript, PDF, SVG 等。功能包括调整，翻转，镜像(mirror)，旋转，扭曲，修剪和变换图像，调整图像颜色，应用各种特殊效果，或绘制文本，线条，多边形，椭圆和贝塞尔曲线等。

## 安装

mac: brew install imagemagick  
ubuntu: sudo apt-get install imagemagick  
源码： [https://github.com/ImageMagick/ImageMagick](https://github.com/ImageMagick/ImageMagick)

## 主要工具  

|命令|描述|
|-|-|
magick | 创建、编辑图像，转换图像格式，以及调整图像大小、模糊、裁切、除去杂点、抖动 ( dither )、绘图、翻转、合并、重新采样等。 
convert | 等同于 magick 命令。 
identify | 输出一个或多个图像文件的格式和特征信息，如分辨率、大小、尺寸、色彩空间等。 
mogrify  | 与 magick 功能一样，不过不需要指定输出文件，自动覆盖原始图像文件。 
composite| 将一个图片或多个图片组合成新图片。 
montage | 组合多个独立的图像来创建合成图像。每个图像都可以用边框，透明度等特性进行装饰。 
compare | 从数学和视觉角度比较源图像与重建图像之间的差异。
display | 在任何 X server 上显示一个图像或图像序列。 
animate | 在任何 X server 上显示图像序列。 
import | 保存 X server 上的任何可见窗口并把它作为图像文件输出。可以捕捉单个窗口，整个屏幕或屏幕的任意矩形部分。 
conjure | 解释并执行 MSL ( Magick Scripting Language ) 写的脚本。 
stream | 一个轻量级工具，用于将图像或部分图像的一个或多个像素组件流式传输到存储设备。在处理大图像或原始像素组件时很有用。  



## 常用操作  

```sh
# 查看信息
magick identify test.png

# 改变尺寸
convert -resize 200x200 test.png test2.png

# 加上透明文本水印。 
convert -draw 'text 0,0 "text"'  -fill 'rgba(221, 34, 17, 0.25)' -pointsize 120 -gravity center joy.jpg watermark.jpg
... 
```


# ffmpeg

强大的视频处理软件([官网](https://ffmpeg.org/download.html) [源码](https://ffmpeg.org/download.html))


## 安装

mac: brew install ffmpeg  
ubuntu: sudo apt-get install ffmpeg  

## 常用操作

1. 视频格式转换
```
ffmpeg -i input.avi output.mp4 
```


2. 提取音频 
```
ffmpeg -i test.mp4 -acodec aac -vn output.aac
```

3. 提取视频
```
ffmpeg -i input.mp4 -vcodec copy -an output.mp4
```

4. 视频剪切
```sh
# 下面的命令，就可以从时间为00:00:15开始，截取5秒钟的视频。
ffmpeg -ss 00:00:15 -t 00:00:05 -i input.mp4 -vcodec copy -acodec copy output.mp4
# -ss表示开始切割的时间，-t表示要切多少。上面就是从开始，切5秒钟出来。
``` 

5. 改变尺寸
```sh
# 将输入的1920x1080缩小到960x540输出:
ffmpeg -i input.mp4 -vf scale=960:540 output.mp4
```
