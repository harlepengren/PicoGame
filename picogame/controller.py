from machine import Pin, ADC

class Input:
    def __init__(self):
        self.key0 = Pin(0,Pin.IN,Pin.PULL_UP)
        self.key1 = Pin(1,Pin.IN,Pin.PULL_UP)
        self.key2 = Pin(21,Pin.IN,Pin.PULL_UP)
        self.key3 = Pin(22,Pin.IN,Pin.PULL_UP)
        
        # Uncomment for joystick
        # self.xAxis = ADC(Pin(27))
        # self.yAxis = ADC(Pin(26))
        
        print("Input initialized . . .")
        
    def getX(self):
        xValue = self.xAxis.read_u16()
        
        if (xValue <= 600):
            return -1
        elif (xValue >=60000):
            return 1
        
        return 0
    
    def getY(self):
        yValue = self.yAxis.read_u16()
        
        if (yValue <= 600):
            return -1
        elif (yValue >=60000):
            return 1
        
        return 0
    
    def getUp(self):
        return not self.key0.value()
    
    def getDown(self):
        return not self.key1.value()
    
    def getA(self):
        return not self.key3.value()
    
    def getB(self):
        pass
    
    def getHome(self):
        return not self.key2.value()