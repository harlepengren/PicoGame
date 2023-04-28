import screen
import image
from machine import Timer, Pin

class PicoGame:
    def __init__(self):
        spriteSize, sprite = image.openImage('sprite.bmp')
        self._spriteBuffer = image.createImageBuffer(sprite,spriteSize)
        
        self._screen = screen.Screen()
        self._screen.clear()
        
        self.x = 0
        self.y = 30

    def draw(self):
        self.x += 1
        
        if self.x > 128:
            self.x = 0
        
        self._screen.fill(0x00)
        self._screen.blit(self._spriteBuffer,x,y)
        self._screen.show()

    def run(self):
        # Set up the timer
        timer = machine.Timer()
        timer.init(mode=machine.Timer.PERIODIC, freq=60, callback=draw)
        
        # Set up the input pins
        key0 = Pin(15, Pin.IN, Pin.PULL_UP)
        key1 = Pin(17, Pin.IN, Pin.PULL_UP)
        key2 = Pin(2, PIN.IN, Pin.PULL_UP)
        
        while(True):
            if not key0:
                # we received the exit button
                break
            
            if not key2:
                x -= 5
                
            if not key1:
                x += 5
            
            
        
        
    

        
    
    
    
    
    