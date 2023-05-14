from machine import Pin, ADC

class Button:    
    def __init__(self,name,pinNumber):
        self.name = name
        self.pin = Pin(pinNumber,Pin.IN,Pin.PULL_UP)
        self.lastState = self.getState()
        
    def getState(self):
        return not self.pin.value()

class Input:
    def __init__(self):
        self.controls = {
            "UP": Button("UP",0),
            "DOWN": Button("DOWN",1),
            "LEFT": Button("LEFT",2),
            "RIGHT": Button("RIGHT",3),
            "HOME": Button("HOME",21),
            "A": Button("A",22),
            "B": Button("B",26)
            }
        
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
    
    def getButtonDown(self,currentButton):
        """Returns true if button was pushed since last time we checked."""
        state = self.controls[currentButton].getState()
        if (state == True) and (state != self.controls[currentButton].lastState):
            self.controls[currentButton].lastState = state
            return True
        
        self.controls[currentButton].lastState = state
        return False
    
    def getButtonReleased(self):
        """Returns true if button was released since last time we checked."""
        state = self.controls[currentButton].getState()
        if (state == False) and (state != self.controls[currentButton].lastState):
            self.controls[currentButton].lastState = state
            return True
        
        self.controls[currentButton].lastState = state
        return False
    
    def getButton(self,currentButton):
        """Returns the current state of the button, either down or up."""
        return self.controls[currentButton].getState()