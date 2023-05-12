"""
Loads a list of games from SD card and allows user to select file.
"""

import machine
from . import sdcard
from . import game
from . import controller
import os

# Load the games from the /games director as a list
# Iterate through list and print the names on the screen
# Add a selection bullet that shows the currently selected
# If user selects a game, load the game

class Menu(game.GameController):
    def __init__(self,path):
        super().__init__()
        self.path = path
        sdcard.mountCard(path)
        self.loadGames(path)
        self.currentSelection = 0
        self.playerInput = controller.Input()
    
    def loadGames(self,path):
        """Load games from path. This function will only return games with .py extension."""
        gameList = os.listdir(path)
        
        # Process the list to remove filename extensions
        deletionList = []
        for index in range(0,len(gameList)):
            extension = gameList[index].find('.py')
            if extension > 0:
                gameList[index] = gameList[index][0:extension]
            else:
                # Not a python file, add to deletion list
                deletionList.append(gameList[index])
                
        for file in deletionList:
            gameList.remove(file)
            
        self.gameList = gameList

    def update(self):
        """Show a list of games on the screen."""
        x = 0
        y = 0
        self.clearScreen()
        for index in range(0,len(self.gameList)):
            if index == self.currentSelection:
                # Draw a rectangle that is 10px high by length of the game name * 10 px
                titleHeight = 10
                titleWidth = len(self.gameList[index])*10
                self._screen.rect(x-2,y-2,x+titleWidth,y+titleHeight,0xffffff,True)
                self.blitText(self.gameList[index],(x,y),0x0)
            else:
                self.blitText(self.gameList[index],(x,y))
            y += 10
            
        # Any user input
        if self.playerInput.getA():
            self.player.position += Vector(0,5)
