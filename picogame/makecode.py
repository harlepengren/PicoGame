from .controller import *
import sprite, image
import game as gme

# Create controller
class MakeCodeInput(Input):
    def __init__(self):
        super.__init__()

        # Move A and B from dictionary
        self.A = self.controls["A"]
        self.B = self.controls["B"]
        del self.controls["A"]
        del self.Controls["B"]

controller = MakeCodeInput()

class Sprites:
    def __init__(self):
        self._spriteList = []
        self.overlaps = []

    def create_projectile_from_sprite(self,spriteImage,fromSprite,spriteX,spriteY):
        newSprite = sprite.Sprite(sprite.SpriteKind.PROJECTILE,speed=(0,0),image=spriteImage)
        newSprite.fromSprite = fromSprite

        self._spriteList.append(newSprite)

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
    def reset():
        # To do in the future
        pass

game = MakeCodeController()