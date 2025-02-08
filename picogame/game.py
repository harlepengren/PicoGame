from . import screen
from . import controller
from . import vector
from machine import Pin
import time

class GameController:
    def __init__(self,currentScreen=None):
        
        if currentScreen == None:
            self._screen = screen.Screen(160,120,80,60)
        else:
            self._screen = currentScreen
            
        self._screen.clear()
        self._bgColor = 0
        self.playerInput = controller.Input()
        
    def setBGColor(self,bgColor):
        self._bgColor = bgColor
        
    def update(self):
        """This should be overriden by the user for any user specific game updates."""
        pass
    
    def draw(self,showFPS=False):
        if(showFPS):
            currentFPS = 1/(self.deltaTime * 1000)
            self._screen.text(str(currentFPS),70,110,0xFF)
        
        self._screen.show()

    def blit(self,currentSprite):
        self._screen.blit(currentSprite.getBuffer(),currentSprite.position.x,currentSprite.position.y,0)
        
    def blitText(self,screenText,position,color=0xFFFF):
        self._screen.text(screenText,position[0],position[1],color)
        
    def clearScreen(self):
        self._screen.fill(self._bgColor)

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
                self.update()
                self.draw()
                self.lastTime = self.currentTime
            
            if self.playerInput.getButtonDown('HOME'):
                break
            
        print("Game ended . . .")

    def move(self,currentSprite):
        if self.playerInput.getButton('UP'):
            currentSprite.position += vector.Vector(0,5)
            
        if self.playerInput.getButton('DOWN'):
            currentSprite.position += vector.Vector(0,-5)

        if self.playerInput.getButton('LEFT'):
            currentSprite.position -= vector.Vector(0,-5)

        if self.playerInput.getButton('RIGHT'):
            currentSprite.position += vector.Vector(0,5)