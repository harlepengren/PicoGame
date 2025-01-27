from machine import Pin,SPI,PWM
import framebuf
import time
import ili9341

SPI = 1
CS = 9
# BL = 13
DC = 13
RST = 10


class Screen(framebuf.FrameBuffer):
    def __init__(self):
        self.width = 240
        self.height = 320
        self.display = ili9341.Display(SPI,CS,DC,10)

        self.buffer = bytearray(self.height * self.width * 2)
        super().__init__(self.buffer, self.width, self.height, framebuf.RGB565) 

        self.WHITE  =   0xFFFF
        self.BLACK  =  0x0000
        self.GREEN  =  0x001F
        self.RED    =  0xF800
        self.BLUE   = 0x07E0
        self.GBLUE = 0X07FF
        self.YELLOW = 0xFFE0
        

    def show(self):
        pass

    def clear(self):
        self.fill(self.BLACK)
        self.show()

    def set_background_color(self,color):
        self.fill(color)
        self.show()

    def color565(self, r, g, b):

        return ili9341.color565(r,g,b)

