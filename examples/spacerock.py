from picogame.makecode import *
from picogame.sprite import *

def on_a_pressed():
    global projectile
    projectile = sprites.create_projectile_from_sprite(img("""
            . d . 
                    . d . 
                    . d . 
                    . . . 
                    . d . 
                    d . d 
                    d . d 
                    . d . 
                    . . . 
                    . d . 
                    . d . 
                    . d .
        """),
        myShip,
        0,
        -150)
controller.A.on_event(ControllerButtonEvent.PRESSED, on_a_pressed)