"""
Loads a list of games from SD card and allows user to select file.
"""

import machine
from . import sdcard
from . import game
import os

# Load the games from the /games director as a list
# Iterate through list and print the names on the screen
# Add a selection bullet that shows the currently selected
# If user selects a game, load the game

class Menu(GameController):
    def __init__(self,path):
        self.path = path
        self.loadGames(path)
    
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

    def showGames(self):
        """Show a list of games on the screen."""
        pass
