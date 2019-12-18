# Avoid the drops
A game for the Arduino requiring an 8x8 LED matrix, a potentiometer, 8 bits of shift register (in one or more chips) and a bar LED.

## How to Play
Using the input from a potentiometer, the goal is to stay alive as long as possible, dipping and dodging the falling raindrops. When you're hit by a drop, you lose a life displayed on the Bar LED and when you lose your last life, the game is over. You can always play again by pressing the Arduino's built-in reset button.

## Installation
Download and move the folders from the Library directory into your arduino's local library folder. [See a tutorial here.](https://www.arduino.cc/en/guide/libraries) Then upload the .ino file to your Arduino!

## Hardware Assembly
A KiCad schematic is conveniently included on how to wire the hardware. Note that the A-788BS LED matrix I used does not have an obvious pinout. See the [datasheet](http://www.topliteusa.com/uploadfile/2014/0825/A-788BS.pdf) for more information. I also used an SNx4HC595 shift register, but any 8 bit or multiple 4 bit shift registers will do the job.

## Configuration
If you happened to wire your Arduino differently, don't worry! The global variables at the top of the program can be changed to accomodate any wiring scheme (Just make sure the pin mode is supported by the Arduino).

If you want to change the width or height of the player paddle, change the appropriate variables in the constructor of the paddle object, just above the setup() loop! 
```c++
Paddle paddle(start_row, start_col, width, height, ...);
```
Note: The start_row and start_col will be almost immediately changed by the potentiometer.
