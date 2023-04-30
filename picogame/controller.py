from machine import Pin

class Input:
    def __init__(self):
        # Set up the input pins
        self.key0 = Pin(15, Pin.IN, Pin.PULL_UP)
        self.buttonA = Pin(17, Pin.IN, Pin.PULL_UP)
        self.buttonB = Pin(2, Pin.IN, Pin.PULL_UP)
        
    def buttonADown(self):
        return not self.buttonA.value()
    
    def buttonBDown(self):
        return not self.buttonB.value()
    
    def key0Down(self):
        return not self.key0.value()