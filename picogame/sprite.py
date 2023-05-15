from . import vector


class SpriteKind():
    PLAYER = 1
    ENEMY = 2
    PROJECTILE = 3
    TILE = 4
    player = 1
    enemy = 2
    projectile = 3

class Sprite:
    """Class to track sprite objects."""
    def __init__(self,kind=SpriteKind.PLAYER, position=(0,0), speed=(0,0), image=None):
        self.kind = kind
        self.position = vector.Vector(position[0],position[1])
        self.x = self.position.x
        self.y = self.position.y
        self.image = image
        self.speed = vector.Vector(speed)
        self.destroyed = False
        self.stay_in_screen = False

        if self.image != None:
            # Set the width and height
            self.width = self.image.size[0]
            self.height = self.image.size[1]
        else:
            self.width = 0
            self.height = 0

    @property
    def x(self):
        return self.position.x
    
    @property
    def y(self):
        return self.position.y

    @x.setter
    def x(self, value):
        self.position.x = value

    @y.setter
    def y(self,value):
        self.position.y = value

    def set_stay_in_screen(self,option):
        self.stay_in_screen = option

    def updatePosition(self):
        if self.kind == SpriteKind.PROJECTILE:
            self.position += self.speed
        elif self.kind == SpriteKind.ENEMY:
            # AI updates
            pass

        # To Do: implement logic for stay_in_screen
    
    def getBuffer(self):
        return self.image.buffer
    
    def destroy(self):
        self.destroyed = True
        
    
        
    