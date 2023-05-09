# Loads a list of games from SD card and allows user to select file
import machine
import sdcard
import uos

def initCard():
    cs = machine.Pin(9, machine.Pin.OUT)
    spi = machine.SPI(1, baudrate=1000000,
                      firstbit=machine.SPI.MSB,
                      sck=machine.Pin(10),
                      mosi=machine.Pin(11),
                      miso=machine.Pin(8))
    
    sd = sdcard.SDCard(spi, cs)
    vfs = uos.VfsFat(sd)
    uos.mount(vfs, '/games')

def loadGames():
    gameList = uos.listdir('/games')
    return gameList