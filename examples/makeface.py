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
        
        self.setBGColor(0xffff)

        # Create my sprites
        self.projectiles = []
        self.enemies = []
        
        # The player
        mytile = Image()
        mytile.createFromString("""
        . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . . 
            . . . 5 . . . . . . 5 . . . . . 
            . . . 5 . . . . . 5 5 . . . . . 
            . . . 5 5 . . . 5 5 . . . . . . 
            . . . . . 5 5 5 5 . . . . . . . 
            . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . .""")
        
        self.mySprite = Sprite(SpriteKind.TILE, image=mytile)
        self.mySprite.position = Vector(50,50)

        imgSprite2 = Image()
        imgSprite2.createFromString("""
        . . . . 7 7 7 . . . . . . . . . 
            . . 7 7 7 7 7 7 7 7 7 7 . . . . 
            . 7 7 7 7 7 7 7 7 7 7 7 7 . . . 
            7 7 7 7 7 7 7 7 7 7 7 7 7 . . . 
            7 7 7 5 5 5 7 7 5 5 5 7 7 7 . . 
            7 7 7 5 5 5 7 7 5 5 5 7 7 7 . . 
            . 7 7 5 5 5 7 7 5 5 5 7 7 7 . . 
            . 7 7 7 7 7 7 7 7 7 7 7 7 7 . . 
            . . 7 7 7 7 7 7 7 7 7 7 7 7 . . 
            . . 7 7 7 7 7 7 7 7 7 7 7 . . . 
            . . . . 7 7 7 7 7 7 7 7 7 . . . 
            . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . .""")

        self.mySprite2 = Sprite(SpriteKind.PLAYER, image=imgSprite2)
        self.mySprite2.position = Vector(50,50)

        imgSprite3 = Image()
        imgSprite3.createFromString("""
        . . . . . . . . . . . . . . . . 
            . . . . 3 3 3 3 3 3 . . . . . . 
            . . . . 3 3 3 3 3 3 . . . . . . 
            . . . . 3 3 3 3 3 3 . . . . . . 
            . . . . 3 3 3 3 3 3 . . . . . . 
            . . . . 3 3 3 3 3 3 . . . . . . 
            . . . . 3 3 3 3 3 3 . . . . . . 
            . . . . 3 3 3 3 3 3 . . . . . . 
            . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . . 
            . . . . . . . . . . . . . . . .""")

        self.player = Sprite(SpriteKind.PLAYER, image=imgSprite3)
        self.player.position = Vector(50,50)
        
    
    def update(self):
        self.clearScreen()
        
        self.move(self.player)
        
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