from vector import Vector


class SpriteKind():
    PLAYER = 1
    ENEMY = 2
    PROJECTILE = 3

class Sprite:
    """Class to track sprite objects."""
    
    def __init__(self,kind=SpriteKind.PLAYER, buffer=None):
        self.kind = kind
        self.position = Vector()
        self.buffer = None
        
    
        
    