from picogame.makecode import *

def on_a_pressed():
    global projectile

controller.A.on_event(ControllerButtonEvent.PRESSED, on_a_pressed)
