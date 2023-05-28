import sys
from picogame.menu import Menu

def run():
    sys.path.insert(0,'/')
    gameMenu = Menu('/games')
    gameMenu.run()

run()