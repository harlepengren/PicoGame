from . import screen
from . import image
from machine import Pin
import time

class GameController:
    def __init__(self):
        self._screen = screen.Screen()
        self._screen.clear()
        self._bgColor = 0
        
    def setBGColor(bgColor):
        self._bgColor = bgColor
        
    def update(self):
        """This should be overriden by the user for any user specific game updates."""
        pass

    def draw(self,userBuffer,showFPS=False):
        if(showFPS):
            currentFPS = 1/(self.deltaTime * 1000)
            self._screen.text(str(currentFPS),70,110,0xFF)
        
        self._screen.show()

    def run(self, fps=60):        
        # Run initial draw
        self.draw()
        
        # Set up the timer
        self.lastTime = time.ticks_ms()
        secondsPerFrame = 1/fps
        
        while(True):
            self.currentTime = time.ticks_ms()
            
            self.deltaTime = time.ticks_diff(self.currentTime,self.lastTime)
            if  self.deltaTime > secondsPerFrame:
                update()
                self.draw()
                self.lastTime = self.currentTime