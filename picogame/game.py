from . import screen
from . import image
from machine import Pin
import time

class PicoGame:
    def __init__(self):
        spriteSize, sprite = image.openImage('sprite.bmp')
        self._spriteBuffer = image.createImageBuffer(sprite,spriteSize)
        
        self._screen = screen.Screen()
        self._screen.clear()
        
        self.x = 0
        self.y = 30

    def draw(self,showFPS=False):
        self.x += 1
        
        if self.x > 128:
            self.x = 0
        
        self._screen.fill(0x00)
        self._screen.blit(self._spriteBuffer,self.x,self.y)
        
        if(showFPS):
            currentFPS = 1/self.deltaTime
            self._screen.text(str(currentFPS),70,110,0xFF)
        
        
        self._screen.show()

    def run(self,fps=60):
        
        # Set up the input pins
        key0 = Pin(15, Pin.IN, Pin.PULL_UP)
        key1 = Pin(17, Pin.IN, Pin.PULL_UP)
        key2 = Pin(2, Pin.IN, Pin.PULL_UP)
        
        # Run initial draw
        self.draw()
        
        # Set up the timer
        self.lastTime = time.ticks_ms()
        secondsPerFrame = 1/fps
        
        while(True):
            self.currentTime = time.ticks_ms()
            
            self.deltaTime = time.ticks_diff(self.currentTime,self.lastTime)
            if  self.deltaTime > secondsPerFrame:
                self.draw(True)
                self.lastTime = self.currentTime
            
            if not key0.value():
                # we received the exit button
                break
            
            if not key2.value():
                self.y -= 5
                
            if not key1.value():
                self.y += 5
        
        
            
            
        
        
    

        
    
    
    
    
    