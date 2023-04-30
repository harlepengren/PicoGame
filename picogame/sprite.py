from vector import Vector


class SpriteKind():
    PLAYER = 1
    ENEMY = 2
    PROJECTILE = 3

class Sprite:
    """Class to track sprite objects."""
    def __init__(self,kind=SpriteKind.PLAYER, position=(0,0), speed=(0,0), image=None):
        self.kind = kind
        self.position = Vector(position[0],position[1])
        self.image = image
        
    def updatePosition():
        if self.kind == PROJECTILE:
            self.position += self.speed
        elif self.kind == ENEMY:
            # AI updates
            pass
        
    
        
    