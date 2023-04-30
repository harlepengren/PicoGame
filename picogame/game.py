from . import screen
from . import image
from machine import Pin
import time

class GameController:
    def __init__(self):
        self._screen = screen.Screen()
        self._screen.clear()

    def draw(self,showFPS=False):
        self._screen.fill(0x00)
        self._screen.blit(self._spriteBuffer,self.x,self.y)
        
        if(showFPS):
            currentFPS = 1/(self.deltaTime * 1000)
            self._screen.text(str(currentFPS),70,110,0xFF)
        
        
        self._screen.show()

    def run(self,fps=60):
        

        
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
            

        
        
            
            
        
        
    

        
    
    
    
    
    