from machine import Pin,SPI
import time
import ili9341

width = 240
height = 320

def run(bg=0):
    sck = 14
    mosi = 15
    dc = 13
    rst = 10
    cs = 9

    spi = SPI(1,40000_000,polarity=0, phase=0,sck=Pin(sck),mosi=Pin(mosi),miso=None)
    display = ili9341.Display(spi=spi, cs=Pin(cs),dc=Pin(dc), rst=Pin(rst))

    x = int(width/2)
    y = int(height/2)
    radius = 5

    dir_x = 1
    dir_y = 1
    speed = 5

    while(True):
        display.clear(color=bg)
        display.fill_circle(x,y,radius,ili9341.color565(255,0,0))

        # Move x and y
        x += speed * dir_x
        y += speed * dir_y

        if x > (width - radius - 2) or x < (radius+2):
            dir_x *= -1

        if y > (height - radius - 2) or y < (radius+2):
            dir_y *= -1


        time.sleep_ms(33)