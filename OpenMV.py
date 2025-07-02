# 这个示例展示了如何使用OpenMV摄像头进行多颜色色块跟踪。
enable_lens_corr = True#控制是否开启防畸变
import sensor# 导入传感器模块，用于控制摄像头
import time# 导入时间模块，用于延时和帧率计算
from machine import LED# 从machine模块导入LED类，用于控制开发板LED
import math# 导入数学模块，用于角度计算
from pyb import UART# 从pyb模块导入UART类，用于串口通信
from pyb import Pin
import utime


# 定义颜色识别阈值（LAB色彩空间）
thresholds = [
    (53, 76, 22, 81, -15, 75),  # 橙色阈值1
    (78, 99, -53, -30, -38, 0),  # 蓝色阈值2
    (53, 96, -2, 45, -47, -8), # 粉色阈值4
    (58, 75, 57, 127, -49, 37), # 红色阈值8
]


sensor.reset()# 重置并初始化摄像头
sensor.set_pixformat(sensor.RGB565)# 设置像素格式为RGB565（16位彩色）
sensor.set_framesize(sensor.QVGA)# 设置分辨率大小为QVGA (320x240)
sensor.skip_frames(time=2000)# 跳过2秒的帧，让摄像头稳定
sensor.set_auto_gain(False)  # 关闭自动增益（颜色识别需要手动控制增益）
sensor.set_auto_whitebal(False)  # 关闭自动白平衡（颜色识别需要手动控制白平衡）
sensor.set_auto_exposure(False,exposure_us=3650)#手动设置感光度

clock = time.clock()# 创建时钟对象，用于计算帧率



led1 = LED("LED_BLUE")
led2 = LED("LED_GREEN")
led3 = LED("LED_RED")

led1.on()
led2.on()
led3.on()

uart = UART(3, 115200, timeout_char=200)# 初始化UART串口通信（波特率115200）
# 物体通过时间窗口（毫秒）
OBJECT_PASSING_TIME = 3300
# 上次检测到物体的时间
last_object_time = 0
# 上次检测到的颜色
last_detected_color = None
# 上次发送颜色的时间
last_send_time = 0

while True:
    clock.tick()# 更新时钟，计算帧率
    img = sensor.snapshot()# 拍摄一张照片

    sensor.set_saturation(2)#设置饱和度
    sensor.set_contrast(3)#设置对比度

    if enable_lens_corr: img.lens_corr(1.8)#如果enable_lens_corr被True就开启防畸变

    current_time = time.ticks_ms()#更新当前时间
    current_color = None
    color_detected = False
    max_blob_area = 0
    largest_blob = None

    # 先找出最大的色块作为主要物体,pixels_threshold像素数量满足才会被识别，area_threshold边界框面积只有满足了才会被识别
    for blob in img.find_blobs(thresholds, roi=(52,48,134,154), pixels_threshold=2500, area_threshold=1800):
        if blob.pixels() > max_blob_area:
            max_blob_area = blob.pixels()
            largest_blob = blob
            color_detected = True

    # 如果找到了色块，处理它
    if largest_blob:
        blob = largest_blob
        #print("Detected blob code:", blob.code())
        # 绘制图形
        if blob.elongation() > 0.5:
            img.draw_edges(blob.min_corners(), color=(255, 0, 0))#红
            img.draw_line(blob.major_axis_line(), color=(0, 255, 0))#绿
            img.draw_line(blob.minor_axis_line(), color=(0, 0, 255))#蓝

        # 确定颜色代码
        color_code = blob.code()
        if color_code == 1:  # 橙色
            current_color = '1'
        elif color_code == 2:  # 蓝色
            current_color = '2'
        elif color_code == 4:  # 粉色
            current_color = '3'
        elif color_code == 8:  # 红色
            current_color = '4'

        img.draw_rectangle(blob.rect())
        img.draw_cross(blob.cx(), blob.cy())
        img.draw_keypoints(
            [(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20
        )

        # 更新最后检测到物体的时间
        last_object_time = current_time

        # 判断是否需要发送新的颜色信号
        time_since_last_send = time.ticks_diff(current_time, last_send_time)

        # 条件1: 新颜色被检测到
        # 条件2: 相同颜色但已经过了足够长的时间
        if current_color is not None and ((current_color != last_detected_color) or (time_since_last_send > OBJECT_PASSING_TIME)):
            uart.write(current_color.encode())
            print("发送颜色: {}".format(color_code))
            last_detected_color = current_color
            last_send_time = current_time

    # 检查是否长时间没有检测到物体，如果是则重置状态
    time_since_last_object = time.ticks_diff(current_time, last_object_time)
    if time_since_last_object > OBJECT_PASSING_TIME:  # 使用更长的时间窗口确保物体真的离开了
        last_detected_color = None
        print("物体已离开，重置状态")
