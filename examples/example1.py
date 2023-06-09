from picogame.game import GameController
from picogame.sprite import Sprite, SpriteKind
from picogame.image import Image
from picogame.controller import Input
from picogame.vector import Vector
from random import randint
from machine import Timer

class MyGame(GameController):
    def __init__(self,currentScreen):
        super().__init__(currentScreen)
        
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
        
        # Create timer for projectiles
        projectileTimer = Timer()
        projectileTimer.init(mode=Timer.PERIODIC, period=1500, callback=self.createProjectile)
        
        
    def createProjectile(self,timerObject):
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
        projectile = Sprite(SpriteKind.PROJECTILE,position=(128,randint(0,128)),speed=(-2,0),image=projectileImage)
        self.projectiles.append(projectile)
    
    def update(self):
        self.clearScreen()
        
        # Get player input - for now, I am using A and B buttons
        #currentY = self.playerInput.getY()
        if self.playerInput.getButton('UP'):
            self.player.position += Vector(0,5)
            
        if self.playerInput.getButton('DOWN'):
            self.player.position += Vector(0,-5)
        
        # Update enemy and projectile positions
        for currentProjectile in self.projectiles:
            currentProjectile.updatePosition()
            self.blit(currentProjectile)
            
        for currentEnemy in self.enemies:
            currentEnemy.updatePosition()
            self.blit(currentEnemy)
            
        self.blit(self.player)

def run(currentScreen):
    myGame = MyGame(currentScreen)
    myGame.run()