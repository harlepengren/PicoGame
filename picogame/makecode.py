from .controller import *
import sprite, image
import game as gme
import random

# Create controller
class MakeCodeInput(Input):
    def __init__(self):
        super.__init__()

        # Move A and B from dictionary
        self.A = self.controls["A"]
        self.B = self.controls["B"]
        del self.controls["A"]
        del self.Controls["B"]

    def move_sprite(self,currentSprite):
        pass

controller = MakeCodeInput()

class Scene:
    def set_background_image(self,backgroundImage):
        pass

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
        newSprite = sprite.Sprite(sprite.SpriteKind.PROJECTILE,speed=(vx,vy),image=newImage)


    # Add handler for overlaps
    def on_overlap(self, spriteKind1,spriteKind2,callback):
        self.overlaps.append((spriteKind1,spriteKind2,callback))

    def destroy(self,currSprite):
        self._spriteList.remove(currSprite)

def img(newImage):
    return image.Image().createFromString(newImage)

sprites = Sprites()


# Game Controller
class MakeCodeController(gme.GameController):
    def __init__(self):
        super.__init__()
        self.intervalUpdates = []
    
    def update(self):
        # Make sure to check whether destroyed flag is set and handle
        
        # check whether time as passed
        for currentUpdate in self.intervalUpdates:
            if self.deltaTime > currentUpdate[0]:
                currentUpdate[1]()
    
    def on_update_interval(self, interval,callback):
        self.intervalUpdates.append((interval,callback))

    def reset(self):
        # To do in the future
        pass

game = MakeCodeController()

def randint(start,stop):
    return random.randint(start,stop)
