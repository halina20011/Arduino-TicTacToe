# Arduino Tic-Tac-Toe

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
[![You can find the whole instructions here:](https://i.ytimg.com/vi/QE2UWFv8szw/sddefault.jpg)](https://www.youtube.com/watch?v=QE2UWFv8szw)

This project is made for this display:

<div style="text-align:center"><img src="/Images/image.jpg" width="403" height="272.4" />

</br>

<div id="header" align="center">
    <img src="https://github.com/halina20011/halina20011/blob/main/Halina-Circle.png" width="100"/>
    <div id="badges">
        <a href="https://www.youtube.com/channel/UCG0h6r6T1joRASO29JV9qMQ">
            <img src="https://img.shields.io/badge/YouTube-red?style=for-the-badge&logo=youtube&logoColor=white" alt="Youtube Badge"/>
        </a>
        <a href="https://halina20011.github.io/">
            <img src="https://img.shields.io/badge/Website-lightgrey?style=for-the-badge" alt="Website"/>
        </a>
    </div>
</div>