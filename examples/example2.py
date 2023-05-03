from picogame.game import GameController
from picogame.sprite import Sprite, SpriteKind
from picogame.image import Image
from picogame.input import Input
from picogame.vector import Vector
from picogame import collision
from random import randint
from machine import Timer

class MyGame(GameController):
    def __init__(self):
        super().__init__()
        
        # Create my sprites
        self.projectiles = []
        self.enemies = []
        self.score = 0
        
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
        
        self.playerInput = Input()
        
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
        if self.playerInput.getA():
            self.player.position += Vector(0,5)
            
        if self.playerInput.getB():
            self.player.position += Vector(0,-5)
        
        # Update enemy and projectile positions
        for currentProjectile in self.projectiles:
            currentProjectile.updatePosition()
            
        for currentEnemy in self.enemies:
            currentEnemy.updatePosition()
            
        # Collision detection
        collisionList = collision.findColliders(self.player,self.projectiles)
        if len(collisionList) > 0:
            for item in collisionList:
                self.score += 1
                print(self.score)
                self.projectiles.remove(item)
            
        
        # Draw everything
        for currentProjectile in self.projectiles:
            self.blit(currentProjectile)
            
        for currentEnemy in self.enemies:
            self.blit(currentEnemy)
            
        self.blit(self.player)
        self.blitText("Score: " + str(self.score),(50,5))
            
            
if __name__ == '__main__':
    myGame = MyGame()
    myGame.run()