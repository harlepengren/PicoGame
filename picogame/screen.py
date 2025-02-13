from ili9341 import Display, color565
import framebuf
from machine import SPI, Pin

class Screen:
    def __init__(self, buffer_width, buffer_height, x=0, y=0):
        try:
            # Baud rate of 40000000 seems about the max
            spi = SPI(1, baudrate=40000000, sck=Pin(14), mosi=Pin(15))
            self._display = Display(spi, dc=Pin(13), cs=Pin(9), rst=Pin(10),width=320,height=240,rotation=270,mirror=False)
            self._display.clear()
            
            self._x = x
            self._y = y
            self._width = buffer_width
            self._height = buffer_height
            self._buffer = framebuf.FrameBuffer(bytearray(buffer_width*buffer_height*2),buffer_width,buffer_height,framebuf.RGB565)
        
        except KeyboardInterrupt:
            self._display.cleanup()
    
    def clear(self,color=0x0):
        self._buffer.fill(color)
        
    def show(self):
        self._display.block(self._x,self._y,self._width-1,self._height-1,self._buffer)
        
    def blitText(self, text, x, y, color):
        self._buffer.text(text,x,y,color)
        
    def blitRect(self,x,y,w,h,color,filled=True):
        if filled:
            self._buffer.fill_rect(x,y,w,h,color)
        else:
            self._buffer.rect(x,y,w,h,color)
        
