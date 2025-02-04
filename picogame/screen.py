from ili9341 import Display, color565
import framebuf
from machine import SPI, Pin

class Screen:
    def __init__(self, buffer_width, buffer_height, x=0, y=0):
        try:
            # Baud rate of 40000000 seems about the max
            spi = SPI(1, baudrate=40000000, sck=Pin(14), mosi=Pin(15))
            self._display = Display(spi, dc=Pin(13), cs=Pin(9), rst=Pin(10),rotation=0)
            self._display.clear()
            
            self._x = x
            self._y = y
            self._width = buffer_width
            self._height = buffer_height
            self._buffer = framebuf.FrameBuffer(bytearray(buffer_width*buffer_height*2),buffer_width,buffer_height,framebuf.RGB565)
        
        except KeyboardInterrupt:
            self._display.cleanup()
    
    def clear(self,color):
        self._buffer.fill(color)
        self._display.block(self._x,self._y,self._width,self._height,self._buffer)
        
