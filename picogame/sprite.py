class SpriteKind(Enum):
    PLAYER = 1
    ENEMY = 2
    PROJECTILE = 3

class Sprite:
    """Class to track sprite objects."""
    
    def __init__(self,kind=SpriteKind.PLAYER):
        self.kind = kind
        self.position = (0,0)
        
    