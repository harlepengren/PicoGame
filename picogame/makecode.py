from .controller import *
from . import sprite, image
from . import game as gme
import random
import time

# Create controller
class MakeCodeInput(Input):
    def __init__(self):
        super().__init__()

        # Move A and B from dictionary
        self.A = self.controls["A"]
        self.B = self.controls["B"]
        del self.controls["A"]
        del self.controls["B"]

    def move_sprite(self,currentSprite):
        pass

controller = MakeCodeInput()

class Scene:
    def set_background_image(self,backgroundImage):
        pass
    
scene = Scene()

class Sprites:
    def __init__(self):
        self._spriteList = []
        self.overlaps = []

    def create(self,spriteImage,spriteKind):
        newSprite = sprite.Sprite(spriteKind,position=(64,64),image=spriteImage)
        self._spriteList.append(newSprite)

        return newSprite

    def create_projectile_from_sprite(self,spriteImage,fromSprite,spriteX,spriteY):
        newSprite = sprite.Sprite(sprite.SpriteKind.PROJECTILE,speed=(0,0),image=spriteImage)
        newSprite.fromSprite = fromSprite

        self._spriteList.append(newSprite)

        return newSprite

    def create_projectile_from_side(self,newImage,vx,vy):
        scale = 0.02
        newSprite = sprite.Sprite(sprite.SpriteKind.PROJECTILE,speed=(vx*scale,vy*scale),image=newImage)
        
        self._spriteList.append(newSprite)
        return newSprite


    # Add handler for overlaps
    def on_overlap(self, spriteKind1,spriteKind2,callback):
        self.overlaps.append((spriteKind1,spriteKind2,callback))

    def destroy(self,currSprite):
        self._spriteList.remove(currSprite)

def img(newImage):
    myImage = image.Image()
    myImage.createFromString(newImage)
    
    return myImage

sprites = Sprites()


# Game Controller
class MakeCodeController(gme.GameController):
    def __init__(self):
        super().__init__()
        self.intervalUpdates = []
    
    def update(self):
        self.clearScreen()
        # Make sure to check whether destroyed flag is set and handle
        
        # check whether time as passed, this is not very readable, consider a dictionary or a class
        for currentUpdate in self.intervalUpdates:
            currentUpdate[2] -= self.deltaTime
            if currentUpdate[2] <= 0:
                currentUpdate[1]()
                # Reset the timer
                currentUpdate[2] = currentUpdate[0]
                
        #LOOP THROUGH AND BLIT
        for currentSprite in sprites._spriteList:
            currentSprite.updatePosition()
            
            # if the currentSprite is way off the screen and not the player, destroy it
            
            if currentSprite != None:
                self.blit(currentSprite)
    
    def on_update_interval(self, interval,callback):
        # Append to our list of updates. The last item in the tuple is time to next update.
        self.intervalUpdates.append([interval,callback,0])

    def reset(self):
        # To do in the future
        pass

game = MakeCodeController()

def randint(start,stop):
    return random.randint(start,stop)
