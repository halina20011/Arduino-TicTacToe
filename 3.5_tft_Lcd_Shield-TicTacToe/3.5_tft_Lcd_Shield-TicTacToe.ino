/*#################################################################################
 * This project was produced by Halina
 * 
 *  github: https://github.com/halina20011/Arduino-TicTacToe/
 *  YouTube: https://www.youtube.com/watch?v=QE2UWFv8szw&t
 *  
 *  Install Libraries From: Adafruit_GFX.h    - https://github.com/adafruit/Adafruit-GFX-Library
 *                          Adafruit_TFTLCD.h - https://github.com/adafruit/TFTLCD-Library
 *                          TouchScreen.h     - https://github.com/adafruit/Adafruit_TouchScreen
 * 
###################################################################################*/
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>

//Defines settings
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define TS_MINX 122
#define TS_MINY 111
#define TS_MAXX 942
#define TS_MAXY 890

#define YP A3
#define XM A2
#define YM 9
#define XP 8

//Defines colors
#define BLACK   0x0000
#define GRAY    0x8410
#define WHITE   0xFFFF
#define RED     0xF800
#define ORANGE  0xFA60
#define YELLOW  0xFFE0
#define LIME    0x07FF
#define GREEN   0x07E0
#define CYAN    0x07FF
#define AQUA    0x04FF
#define BLUE    0x001F
#define MAGENTA 0xF81F
#define PINK    0xF8FF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

//Set the box to be empty.
bool box1 = false;
bool box2 = false;
bool box3 = false;
bool box4 = false;
bool box5 = false;
bool box6 = false;
bool box7 = false;
bool box8 = false;
bool box9 = false;

//Zero is unoccupied, one is that the field is the First Player and the two is that the field is the Second Player.
int Box1 = 0;
int Box2 = 0;
int Box3 = 0;
int Box4 = 0;
int Box5 = 0;
int Box6 = 0;
int Box7 = 0;
int Box8 = 0;
int Box9 = 0;

//The true is who is playing now.
bool Player1 = true;
bool Player2 = false;

extern uint8_t Tic[];
extern uint8_t Tac[];
extern uint8_t P1[];
extern uint8_t P2[];

void setup() {
  tft.reset(); //Reset display
  tft.begin(0x9341); //If your display does not work, change the address to 0x9325 or 0x9328 or 0x7575 or 0x9341, 0x8357                                                              
  Serial.begin(9600);
  tft.setRotation(1);
  tft.fillScreen(BLACK); //Fill the Screen black
  tft.drawRect(0, 0, 480, 40, BLUE); //Draw Blue line

  tft.drawRect(0, 40, 480, 93, BLUE);
  tft.drawRect(0, 133, 480, 93, BLUE);
  tft.drawRect(0, 226, 480, 93, BLUE);

  tft.drawRect(0, 40, 160, 280, BLUE);
  tft.drawRect(160, 40, 160, 280, BLUE);
  tft.drawRect(320, 40, 160, 280, BLUE);
  drawBitmap(220, 2, P1, 40, 35, RED); //Draw Number of player
}

void loop(void) {
  TSPoint p = ts.getPoint();

  if (p.z > ts.pressureThreshhold) {

    p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, 480);

    //Box1
    if (p.x > 190 && p.x < 290 && p.y < 500 && p.y > 310 && box1 == false) {
      box1 = true;
      Serial.println("Box1");
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      if (Player1 == true) {
        Box1 = 1;
      }
      else {
        Box1 = 2;
      }
      ChangePlayer();
    }

    //Box2
    if (p.x > 190 && p.x < 290 && p.y < 310 && p.y > 130 && box2 == false) {
      box2 = true;
      Serial.println("Box2");
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      if (Player1 == true) {
        Box2 = 1;
      }
      else {
        Box2 = 2;
      }
      ChangePlayer();
    }

    //Box3
    if (p.x > 190 && p.x < 290 && p.y < 130 && p.y > -45 && box3 == false) {
      box3 = true;
      Serial.println("Box3");
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      if (Player1 == true) {
        Box3 = 1;
      }
      else {
        Box3 = 2;
      }
      ChangePlayer();
    }

    //Box4
    if (p.x > 100 && p.x < 190 && p.y < 500 && p.y > 310 && box4 == false) {
      box4 = true;
      Serial.println("Box4");
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      if (Player1 == true) {
        Box4 = 1;
      }
      else {
        Box4 = 2;
      }
      ChangePlayer();
    }

    //Box5
    if (p.x > 100 && p.x < 190 && p.y < 310 && p.y > 130 && box5 == false) {
      box5 = true;
      Serial.println("Box5");
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      if (Player1 == true) {
        Box5 = 1;
      }
      else {
        Box5 = 2;
      }
      ChangePlayer();
    }

    //Box6
    if (p.x > 100 && p.x < 190 && p.y < 130 && p.y > -45 && box6 == false) {
      box6 = true;
      Serial.println("Box6");
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      if (Player1 == true) {
        Box6 = 1;
      }
      else {
        Box6 = 2;
      }
      ChangePlayer();
    }

    //Box7
    if (p.x > 0 && p.x < 100 && p.y < 500 && p.y > 310 && box7 == false) {
      box7 = true;
      Serial.println("Box7");
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      if (Player1 == true) {
        Box7 = 1;
      }
      else {
        Box7 = 2;
      }
      ChangePlayer();
    }

    //Box8
    if (p.x > 0 && p.x < 100 && p.y < 310 && p.y > 130 && box8 == false) {
      box8 = true;
      Serial.println("Box8");
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      if (Player1 == true) {
        Box8 = 1;
      }
      else {
        Box8 = 2;
      }
      ChangePlayer();;
    }

    //Box9
    if (p.x > 0 && p.x < 100 && p.y < 130 && p.y > -45 && box9 == false) {
      box9 = true;
      Serial.println("Box9");
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      if (Player1 == true) {
        Box9 = 1;
      }
      else {
        Box9 = 2;
      }
      ChangePlayer();
    }
  }

  //Box1
  if (Box1 == 1) {
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    drawBitmap(35, 40, Tic, 90, 90, RED); //141, 40, Tic, 90, 90, RED
  }
  else if (Box1 == 2) {
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    drawBitmap(35, 40, Tac, 90, 90, BLUE);
  }

  //Box2
  if (Box2 == 1) {
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    drawBitmap(195, 40, Tic, 90, 90, RED);
  }
  else if (Box2 == 2) {
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    drawBitmap(195, 40, Tac, 90, 90, BLUE);
  }

  //Box3
  if (Box3 == 1) {
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    drawBitmap(335, 40, Tic, 90, 90, RED);
  }
  else if (Box3 == 2) {
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    drawBitmap(335, 40, Tac, 90, 90, BLUE);
  }

  //Box4
  if (Box4 == 1) {
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    drawBitmap(35, 133, Tic, 90, 90, RED);
  }
  else if (Box4 == 2) {
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    drawBitmap(35, 133, Tac, 90, 90, BLUE);
  }

  //Box5
  if (Box5 == 1) {
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    drawBitmap(195, 133, Tic, 90, 90, RED);
  }
  else if (Box5 == 2) {
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    drawBitmap(195, 133, Tac, 90, 90, BLUE);
  }

  //Box6
  if (Box6 == 1) {
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    drawBitmap(335, 133, Tic, 90, 90, RED);
  }
  else if (Box6 == 2) {
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    drawBitmap(335, 133, Tac, 90, 90, BLUE);
  }

  //Box7
  if (Box7 == 1) {
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    drawBitmap(35, 226, Tic, 90, 90, RED);
  }
  else if (Box7 == 2) {
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    drawBitmap(35, 226, Tac, 90, 90, BLUE);
  }

  //Box8
  if (Box8 == 1) {
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    drawBitmap(195, 226, Tic, 90, 90, RED);
  }
  else if (Box8 == 2) {
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    drawBitmap(195, 226, Tac, 90, 90, BLUE);
  }

  //Box9
  if (Box9 == 1) {
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    drawBitmap(335, 226, Tic, 90, 90, RED);
  }
  else if (Box9 == 2) {
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    drawBitmap(335, 226, Tac, 90, 90, BLUE);
  }


  if (Box1 == 1 && Box2 == 1 && Box3 == 1 || Box4 == 1 && Box5 == 1 && Box6 == 1 || Box7 == 1 && Box8 == 1 && Box9 == 1 || Box1 == 1 && Box5 == 1 && Box9 == 1  || Box3 == 1 && Box5 == 1 && Box7 == 1 ||  Box1 == 1 && Box4 == 1 && Box7 == 1 || Box2 == 1 && Box5 == 1 && Box8 == 1 || Box3 == 1 && Box6 == 1 && Box9 == 1) {
    Box1 = 0;
    Box2 = 0;
    Box3 = 0;
    Box4 = 0;
    Box5 = 0;
    Box6 = 0;
    Box7 = 0;
    Box8 = 0;
    Box9 = 0;
    tft.fillScreen(BLACK);
    tft.setCursor(200, 160);
    tft.setTextColor(RED);
    tft.setTextSize(2);
    tft.print("Player 1 Victory");
  }

  if (Box1 == 2 && Box2 == 2 && Box3 == 2 || Box4 == 2 && Box5 == 2 && Box6 == 2 || Box7 == 2 && Box8 == 2 && Box9 == 2 || Box1 == 2 && Box5 == 2 && Box9 == 2  || Box3 == 3 && Box5 == 2 && Box7 == 2 || Box1 == 2 && Box4 == 2 && Box7 == 2 || Box2 == 2 && Box5 == 2 && Box8 == 2 || Box3 == 2 && Box6 == 2 && Box9 == 2) {
    Box1 = 0;
    Box2 = 0;
    Box3 = 0;
    Box4 = 0;
    Box5 = 0;
    Box6 = 0;
    Box7 = 0;
    Box8 = 0;
    Box9 = 0;
    tft.fillScreen(BLACK);
    tft.setCursor(200, 160);
    tft.setTextColor(BLUE);
    tft.setTextSize(2);
    tft.print("Player 2 Victory");
  }
}

void ChangePlayer() {
  if (Player1 == true) {
    Player1 = false;
    Player2 = true;
    Serial.println("1");
    drawBitmap(220, 2, P1, 40, 35, BLACK);
    drawBitmap(220, 2, P2, 40, 35, RED);
  }
  else if (Player2 == true) {
    Player2 = false;
    Player1 = true;
    Serial.println("2");
    drawBitmap(220, 2, P2, 40, 35, BLACK);
    drawBitmap(220, 2, P1, 40, 35, RED);
  }
}

void drawBitmap(int16_t x, int16_t y,
                const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {

  int16_t i, j, byteWidth = (w + 7) / 8;
  uint8_t byte;

  for (j = 0; j < h; j++) {
    for (i = 0; i < w; i++) {
      if (i & 7) byte <<= 1;
      else      byte   = pgm_read_byte(bitmap + j * byteWidth + i / 8);
      if (byte & 0x80) tft.drawPixel(x + i, y + j, color);
    }
  }
}
