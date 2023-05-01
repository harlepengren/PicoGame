from machine import Pin, ADC

class Controller:
    def __init__():
        self.key0 = Pin(0,Pin.IN,Pin.PULL_UP)
        self.key1 = Pin(1,Pin.IN,Pin.PULL_UP)
        self.key2 = Pin(2,Pin.IN,Pin.PULL_UP)
        self.key3 = Pin(3,Pin.IN,Pin.PULL_UP)
        
        self.xAxis = ADC(Pin(27))
        self.yAxis = ADC(Pin(26))
        
    def getX():
        xValue = self.xAxis.read_u16()
        return (xValue <= 600) or (xValue >= 60000)
    
    def getY():
        yValue = self.yAxis.read_u16()
        return (yValue <= 600) or (yValue >= 60000)
    
    def getA():
        return not self.key0.value()
    
    def getB():
        return not self.key1.value()