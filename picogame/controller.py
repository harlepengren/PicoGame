from machine import Pin

class Input:
    def __init__:
        # Set up the input pins
        key0 = Pin(15, Pin.IN, Pin.PULL_UP)
        buttonA = Pin(17, Pin.IN, Pin.PULL_UP)
        buttonB = Pin(2, Pin.IN, Pin.PULL_UP)
        
    def buttonADown():
        return not buttonA.value()
    
    def buttonBDown():
        return not buttonB.value()
    
    def key0Down():
        return not key0.value()