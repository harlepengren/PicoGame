from .controller import *
from . import sprite, image
from . import game as gme
from . import vector
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
        
        self.currentSprite = None

    def checkButtons(self):
        self.A.checkEvent()
        self.B.checkEvent()

    def move_sprite(self,currentSprite):
        self.currentSprite = currentSprite
        
    def moveCurrentSprite(self):
        if self.currentSprite != None:
            if self.getButton('UP'):
                self.currentSprite.position += vector.Vector(0,5)
            
            if self.getButton('DOWN'):
                self.currentSprite.position += vector.Vector(0,-5)
                
            if self.getButton('LEFT'):
                self.currentSprite.position += vector.Vector(-5,0)
            
            if self.getButton('RIGHT'):
                self.currentSprite.position += vector.Vector(5,0)

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

    def create_projectile_from_sprite(self,spriteImage,fromSprite,vx,vy):
        scale = 0.02
        newSprite = sprite.Sprite(sprite.SpriteKind.PROJECTILE,position=(fromSprite.x,fromSprite.y),speed=(vx*scale,vy*scale),image=spriteImage)

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
        
        # Process input
        controller.moveCurrentSprite()
        controller.checkButtons()
        
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
        print("reset")

game = MakeCodeController()

def randint(start,stop):
    return random.randint(start,stop)
