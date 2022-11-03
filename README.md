# Arduino Tic-Tac-Toe

Text tutorial: https://halina20011.github.io/Arduino/ArduinoTicTacToe.html

## Required libraries
To successfully compile code, you will need to download these libraries:</br>

- TFTLCD Library: https://github.com/adafruit/TFTLCD-Library
- GFX Library: https://github.com/adafruit/Adafruit-GFX-Library
- TouchScreen: https://github.com/adafruit/Adafruit_TouchScreen

## Set correct display size
Adafruit TFT library has by default width 240 and height 320. This display has width 320 and height 480.
To set correct sizes got to Arduino libraries folder and edit ```Adafruit_TFT/Adafruit_TFTLCD.cpp```.

Find lines with
```
#define TFTWIDTH 240
#define TFTHEIGHT 320
```
and change it to (you can also comment previous sizes and add this)
```
#define TFTWIDTH 320
#define TFTHEIGHT 480
```

## You can find the whole instructions here
[![You can find the whole instructions here:](https://img.youtube.com/vi/QE2UWFv8szw/maxresdefault.jpg)](https://www.youtube.com/watch?v=QE2UWFv8szw)

</br>

## Images:
<div style="text-align:center">
    <img src="https://halina20011.github.io/Images/arduinoTicTacToeImage1.jpg"/>
    <img src="/Images/image.jpg"/><div>
</div>