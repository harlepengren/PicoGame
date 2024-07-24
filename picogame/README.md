This folder is the original Python version of the game engine.

# Hardware
For this example, we are using a [Raspberry Pi Pico](https://www.raspberrypi.com/products/raspberry-pi-pico/) connected to a ST7735S LCD screen (in our case [Waveshare Pico LCD 1.44](https://www.waveshare.com/wiki/Pico-LCD-1.44)). See [here](https://www.waveshare.com/wiki/Pico-LCD-1.44) for wiring the LCD screen to the Pico.

# Install the Game Engine
To install the PicoGame game engine, simply download the picogame folder and upload it to your Pico device. Uploading with [Thonny](https://www.freva.com/transfer-files-between-computer-and-raspberry-pi-pico/) is very easy, but you can also upload by [command line](https://mikeesto.medium.com/uploading-to-the-raspberry-pi-pico-without-thonny-53de1a10da30).

# Playing an Example Game
The example folder contains several example games. To play, choose an example game from the examples folder. Upload it to root (/) on the Pico. Change the name of the file to main.py. Restart the Pico (in Thonny you can click the stop sign).

# Creating Your Own Game
Once you are ready to graduate beyond the examples, creating your own game is easy. You simply need to create assets, load them, and create the update function that is called every iteration of the game loop.

## Create Your Assets
You can create assets in two ways. First, you can create bitmap images in an image editor. Second, and perhaps easier, you can create assets in MakeCode Arcade. Simply go into the image editor and create your image. Once done, you can switch to the code view and copy the image text. You can then use the Image.createFromString method to create the image buffer.

## Subclass the Game Controller
PicoGame takes care of the screen drawing for you. All you need to do is take care of telling the engine what to draw. You can do this by creating a subclass of the game controller.

`class YourClassName(GameController)`

You then create two methods:
- `__init__()`
- `update()`

`__init__()` handles initialization. Ensure you call 'super().__init__()'. In this method, place any code to load assets or set up the AI. In example1.py, we also created lists to manage enemies and projectiles. We also created a projectile timer that is called every 1.5 seconds to create a new projectile.

The `update()` function handles everything we need to do to update a frame. First, we check for user input using the Input class. Next, we move the projectiles and enemies. Finally, we draw everything to the screen using the blit method.

## Running the Game
To run the game, upload the file to the Pico.

```python
import yourfile.py
yourClass = YourClass()
yourClass.run()
```
