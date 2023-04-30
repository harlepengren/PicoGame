from picogame.game import GameController
from picogame.sprite import Sprite, SpriteKind
from picogame.image import Image
from picogame.controller import Input
from random import randint


class MyGame(GameController):
    def __init__(self):
        super().__init__()
        
        # Create my sprites
        self.projectiles = []
        self.enemies = []
        
        # The player
        playerImage = Image()
        playerImage.createFromString("""
        . . . . . . f f f f f f . . . . 
            . . . . . f 1 1 1 1 1 1 f . . . 
            . . . . f 1 1 1 1 1 1 1 1 f . . 
            . . . f 1 f 1 1 1 1 1 1 1 1 f . 
            . . . f f 1 1 1 1 1 1 1 1 1 f . 
            . . . f 1 f 1 1 f 1 1 f 1 1 f . 
            . . . f f 1 1 1 1 1 1 1 1 1 f . 
            . . f f 1 f 1 f 1 1 1 1 1 f . . 
            . f 1 1 f 1 f 1 f f f f f . . . 
            f 1 1 1 f f f 1 1 1 1 1 1 f . . 
            f f 1 f 1 f 1 f f 1 1 1 1 1 f . 
            . . f 1 f 1 f 1 f 1 1 1 1 1 f f 
            . . f f 1 f 1 f 1 f 1 1 1 f 1 f 
            . . f f f 1 f 1 f 1 f 1 f 1 f f 
            . . . f 1 f 1 f 1 f 1 f 1 f f . 
            . . . . f f f f f f f f f f . .""")
        self.player = Sprite(SpriteKind.PLAYER, image=playerImage)
        
        # Projectile
        projectileImage = Image()
        projectileImage.createFromString("""
            . . . . . . . . . . . . . . . . 
                    . . . . . . . . . . . . . . . . 
                    . . . . . . . . . . . . . . . . 
                    . . . . . . f f f f f f . . . . 
                    . . . . . f f f 1 1 1 1 f . . . 
                    . . . . f f 1 1 f f 1 f 1 f . . 
                    . . . . f 1 f 1 f f 1 f 1 1 f . 
                    . f f f f f 1 f 1 1 1 1 f 1 f . 
                    f 1 1 1 f f f 1 f 1 1 f 1 f 1 f 
                    f f 1 1 1 1 f f 1 f f 1 f 1 f . 
                    f 1 f 1 1 1 1 f f 1 1 1 1 f . . 
                    f f 1 f 1 1 1 f 1 1 1 1 1 1 f . 
                    f 1 f 1 f f f 1 f 1 1 1 1 1 f . 
                    . f 1 f 1 f 1 f 1 f 1 f 1 1 f . 
                    . . f 1 f 1 f 1 f 1 f 1 f f . . 
                    . . . f f f f f f f f f f . . .""")
        projectile = Sprite(SpriteKind.PROJECTILE,position=(128,randint(0,128)),speed=(0,-10),image=projectileImage)
        self.projectiles.append(projectile)
        
        self.playerInput = Input()
        
    
    def update(self):
        super().update()
        
        # Get player input
        if self.playerInput.buttonADown():
            self.player.position += Vector(0,5)
            
        if self.playerInput.buttonBDown():
            self.player.position += Vector(0,-5)
        
        # Update enemy and projectile positions
        for currentProjectile in self.projectiles:
            currentProjectile.updatePosition()
            
        for currentEnemy in self.enemies:
            currentEnemy.updatePosition()
            
        self.blit(self.player)
            
        
            

myGame = MyGame()
myGame.run()