# PicoGame

PicoGame is a tiny game engine designed to run simple games on the Raspberry Pi Pico. If you want more information on the development of PicoGame as well as our 

# The Hardware
For this game engine, we are using a [Raspberry Pi Pico](https://www.raspberrypi.com/products/raspberry-pi-pico/) connected to a [2.2" TFT LCD Display](https://www.adafruit.com/product/1480) using the [ili9341 driver] (https://cdn-shop.adafruit.com/datasheets/ILI9341.pdf). We use the Serial Peripheral Interface (SPI) standard to communicate from the Pico to the screen.

# Using the Game Engine
There are two ways to use the game engine:
- C/C++: The engine can be called directly in C/C++ if the game is written in C/C++.
- Micropython Module: The game engine can be compiled into a micropython module allowing the games to be written in Python.

## Micropython Module
After cloning the repository, you need to get Micropython as a submodule.

    $ git submodule update --init

Get the micropython submodules:

    $ cd micropython
    $ git submodule update --init

Compile mpy-cross, which is required for the ports:
    $ cd mpy-cross
    $ make

Build the module in the ports/rp2 folder:
    $ cd ports/rp2
    $ make USER_C_MODULES=../../../module/pciogame.cmake

## Using the Engine
Connect the board to your computer using bootsel mode. Copy firmware.uf2 into the Raspberry Pico folder. This will cause the Raspberry Pico to reboot. I use [Thonny](https://thonny.org) for Micropython.

`import PicoGame`

Currently, there are two classes:
- PicoInput: handles input operations
- PicoScreen: handles screen drawing

For example, to clear the screen with a blue background:
`import PicoGame
screen = PicoGame.PicoScreen()
screen.clear_screen(0x421d)
screen.render()`