/*#################################################################################
   This project was produced by Halina

    github: https://github.com/halina20011/Arduino-TicTacToe/
    YouTube: https://www.youtube.com/channel/UCG0h6r6T1joRASO29JV9qMQ

    Install Libraries From: Adafruit_GFX.h    - https://github.com/adafruit/Adafruit-GFX-Library
                            Adafruit_TFTLCD.h - https://github.com/adafruit/TFTLCD-Library
                            TouchScreen.h     - https://github.com/adafruit/Adafruit_TouchScreen

###################################################################################*/

#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>
#include "Fonts/FreeSans9pt7b.h"
#include "colors.h"

//Defines setti2gs
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define TS_MINX 112
#define TS_MINY 94

#define TS_MAXX 905
#define TS_MAXY 956

#define YP A3
#define XM A2
#define YM 9
#define XP 8

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 100);

char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

char human = 'x';
char ai = 'o';

char currentPlayer = human;

int xColor = blue;
int oColor = red;

int infinity = 32767;

extern uint8_t oChar[];
extern uint8_t xChar[];

String mode = "None";

int padding = 25;
int xOffset = 160;
int nextPos = 90;
int width = 270;
int height = 6;
int radius = 2;

int charArea = 90;
int charSize = charArea - 2 * height;

bool winnerWasDrawn = false;

int messageIndex = 0;
int allCalculatedMoves = 0;

void(* resetFunc) (void) = 0;

void setup(){
    Serial.begin(115200);

    //Reset display
    tft.reset(); 
    //If your display does not work, change the address to 0x9325 or 0x9328 or 0x7575 or 0x9341, 0x8357
    tft.begin(0x9341); 
    tft.setRotation(3);
    tft.setTextWrap(false);
    tft.setTextColor(black);
    tft.setFont(&FreeSans9pt7b);
    tft.fillScreen(black); //Fill the Screen black
    tft.setTextSize(2);

    // Draw Game scene
    drawInfoArea();
    drawGameArea();

    // Print text
    tft.setTextColor(blue);
    drawCentreString("Tic-tac-toe", 160, 0, 320, 320);
    tft.setTextColor(black);

    // Wait to mode to be selected
    selectMode();

    drawInfoArea();
    drawGameArea();
    drawGameField();

    printTurn();
}

void loop(){
    TSPoint p = ts.getPoint();

    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    if(p.z > ts.pressureThreshhold) {
        int y = map(p.x, TS_MAXX, TS_MINX, 0, 320);
        int x = map(p.y, TS_MAXY, TS_MINY, 0, 480);

        if(winnerWasDrawn == true){
            if(10 < x && x < 10 + 140 && 260 < y && y < 260 + 50){
                Serial.println("Reseting...");
                resetFunc();
            }
        }

        for(int _y = 0; _y < 3; _y++){
            for(int _x = 0; _x < 3; _x++){
                int xPos = xOffset + padding + nextPos * _x;
                int yPos = padding + nextPos * _y;

                if(xPos < x && x < xPos + nextPos && yPos < y && y < yPos + nextPos){
                    move(_x, _y);
                    break;
                }
            }
        }
    }
}

void selectMode(){
    tft.fillRoundRect(10,  10, 140, 50, 8, red);     //Solo "button"
    tft.fillRoundRect(10,  70, 140, 50, 8, blue);    //Duo  "button"
    tft.fillRoundRect(10, 260, 140, 50, 5, lime);  //Help "button"

    drawCentreString("Solo", 10,  10, 140, 50);
    drawCentreString("Duo",  10,  70, 140, 50);
    drawCentreString("Help", 10, 260, 140, 50);

    while(mode == "None"){
        TSPoint p = ts.getPoint();

        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);
        if (p.z > ts.pressureThreshhold) {
            int y = map(p.x, TS_MAXX, TS_MINX, 0, 320);
            int x = map(p.y, TS_MAXY, TS_MINY, 0, 480);
            
            Serial.println("x: " + String(x) + " y: " + String(y));
            if (10 < x && x < 150 && 10 < y  && y < 60) {
                mode = "Solo";
            }
            else if (10 < x && x < 150 && 70 < y  && y < 120) {
                mode = "Duo";
            } 
            else if (10 < x && x < 150 && 260 < y && y < 310) {
                help();
            } 
        }
    }
    Serial.println("Selected mode: " + mode);
}

// Show help menu
void help(){
    typedef struct text {
        int textSize;
        String message;
    };

    drawInfoArea();
    drawGameArea();

    tft.setTextColor(blue);

    int cursorX = xOffset + padding;
    int cursorY = padding;

    text array[] = {
        {1, "There are to mods from which you"},
        {1, "can sellect one."},
        {1, ""},
        {2, "Solo"},
        {1, ""},
        {1, "Mode where you play against Ai."},
        {1, "First move will be slow,"},
        {1, "because it need to calculate more"},
        {1, "than ten thousands of moves."},
        {1, ""},
        {2, "Duo"},
        {1, ""},
        {1, "Mode where you play with"},
        {1, "somebody else."},
    };

    int textSize = 9;
    int textGap = 8;

    for(int i = 0; i < 14; i++){
        int pos = cursorY + array[i].textSize * textSize + array[i].textSize * textGap;
        tft.setCursor(cursorX, pos);
        tft.setTextSize(array[i].textSize);
        tft.print(array[i].message);

        cursorY = pos;
    }
    tft.setTextSize(2);

    tft.fillRoundRect(10, 260, 140, 50, 5, lime);
    drawCentreString("Return", 10, 260, 140, 50);
    while(true){
        TSPoint p = ts.getPoint();

        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);
        if (p.z > ts.pressureThreshhold) {
            int y = map(p.x, TS_MAXX, TS_MINX, 0, 320);
            int x = map(p.y, TS_MAXY, TS_MINY, 0, 480);

            if(10 < x && x < 10 + 260 && x < 260 && x < 260 + 50){
                resetFunc();
                break;
            }
        }
    }
}

// Functions to clear display area
void drawInfoArea(){
    tft.fillRect(0, 0, 160, 320, white);
}

void drawGameArea(){
    tft.fillRect(160, 0, 320, 320, black);
}

void drawGameField(){
    tft.fillRoundRect(xOffset + padding + nextPos * 1 - height, padding, height, width, radius, blue);
    tft.fillRoundRect(xOffset + padding + nextPos * 2 - height, padding, height, width, radius, blue);

    tft.fillRoundRect(xOffset + padding, padding + nextPos * 1 - height, width, height, radius, blue);
    tft.fillRoundRect(xOffset + padding, padding + nextPos * 2 - height, width, height, radius, blue);
}

void drawChar(int y, int x, char character){
    int X = xOffset + padding + x * nextPos + height / 2;
    int Y = padding + y * nextPos + height / 2;

    if(character == 'x'){
        drawBitmap(X, Y, xChar, charSize, charSize, blue);
    }
    else{
        drawBitmap(X, Y, oChar, charSize, charSize, red);
    }
}

// Show additional informations on the screen
void printTurn(){
    if(currentPlayer == 'x'){
        tft.setTextColor(xColor);
    }
    else{
        tft.setTextColor(oColor);
    }
    tft.fillRect(0, 10, 160, 80, white);
    tft.setCursor(20, 80 * 3/4);
    tft.print(String(currentPlayer));
    tft.setTextColor(black);
    tft.print(" 's turn");
}

void printAiMoves(String message, int messageIndex){
    tft.setTextColor(red);
    tft.setTextSize(1);
    int height = 30;
    int pos = 90 + messageIndex * height;

    tft.fillRect(0, pos, 160, 30, white);
    drawString(message, 0, pos, 30);

    tft.setTextSize(2);
    tft.setTextColor(black);
}

// Functions for the game logic
void move(int x, int y) {
    Serial.println("Move X: " + String(x) + " Y: " + String(y) + " ");
    if(board[y][x] != ' ') {
        return;
    }

    board[y][x] = currentPlayer;
    drawChar(y, x, currentPlayer);

    changePlayer();
    printTurn();

    String result = getGameStatus();
    if(result != ""){        
        showWinner(result);
        return;
    }

    if(mode == "Solo" && currentPlayer == ai){
        Serial.println("Ai move");
        moveAi();
    }
}

void changePlayer() {
    if (currentPlayer == 'x') {
        currentPlayer = 'o';
    }
    else {
        currentPlayer = 'x';
    }
}

String getGameStatus() {
    String winner = "";
    for (int i = 0; i < 3; i++) {
        if (isEquals(board[i][0], board[i][1], board[i][2]) == true) {
            winner = String(board[i][0]);
        }
    }

    for (int i = 0; i < 3; i++) {
        if (isEquals(board[0][i], board[1][i], board[2][i]) == true) {
            winner = String(board[0][i]);
        }
    }

    if (isEquals(board[0][0], board[1][1], board[2][2]) == true) {
        winner = String(board[0][0]);
    }
    if (isEquals(board[2][0], board[1][1], board[0][2]) == true) {
        winner = String(board[2][0]);
    }

    int freeSpots = 0;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (board[y][x] == ' ') {
                freeSpots++;
            }
        }
    }

    if (winner == "" && freeSpots == 0) {
        return "tie";
    }
    else {
        return winner;
    }
}

void showWinner(String result){
    if(winnerWasDrawn == true){
        return;
    }

    Serial.println("Winner: " + result);
    tft.fillRoundRect(10, 260, 140, 50, 5, green);
    drawCentreString("Reset", 10, 260, 140, 50);

    winnerWasDrawn = true;
    if(result == "tie"){
        drawGameArea();
        tft.setTextColor(blue);
        drawCentreString("Tie", 160, 0, 480 - 160, 320);
        return;
    }

    int height = 6;
    int x = xOffset + padding + charArea / 2;
    int y = padding + charArea / 2 - height;

    for (int i = 0; i < 3; i++) {
        if (isEquals(board[i][0], board[i][1], board[i][2]) == true) {
            y += i * nextPos;
            plotLineWidth(x, y, x + charArea * 2, y, height, white);
        }
    }

    for (int i = 0; i < 3; i++) {
        if (isEquals(board[0][i], board[1][i], board[2][i]) == true) {
            x += i * nextPos;
            plotLineWidth(x, y, x, y + charArea * 2, height, white);
        }
    }

    if (isEquals(board[0][0], board[1][1], board[2][2]) == true) {
        plotLineWidth(x, y, x + charArea * 2, y + charArea * 2, height, white);
    }

    if (isEquals(board[2][0], board[1][1], board[0][2]) == true) {
        plotLineWidth(x, y + charArea * 2, x + charArea * 2, y, height, white);
    }
}

bool isEquals(char a, char b, char c) {
    if (a == b && b == c && a != ' ') {
        return true;
    }
    return false;
}

int getScore(String resurlt, char Player){
    String player = String(Player);
    if(resurlt == player){
        return 10;
    }
    else if(resurlt != "tie"){
        return -10;
    }
    return 0;
}

void printBoard(char Board[3][3]){
    Serial.print("[");
    for (int y = 0; y < 3; y++) {
        Serial.print("[");
        for (int x = 0; x < 3; x++) {
            Serial.print(String(Board[y][x]));
            Serial.print(" ");
        }
        Serial.print("]");
    }
    Serial.println("]");

    return;
}

int getBestMove(char Board[3][3], boolean isCalculatedPlayer, char calculatedPlayer, char oponent, int maxDepth) {
    String resurlt = getGameStatus();
    if (resurlt != "") {
        return getScore(resurlt, calculatedPlayer) * maxDepth;
    }
    allCalculatedMoves++;
    int bestScore = 0;
    if(isCalculatedPlayer == true){
        bestScore = -infinity;
    }
    else{
        bestScore = infinity;
    }

    // This function will print all possible combinations, but when you 
    // enable it it will significantly slow down the code.
    // Could be fixed by increasing the baud rate of serial communication.
    // printBoard(Board);

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (board[y][x] == ' ') {
                if(isCalculatedPlayer == true){
                    board[y][x] = calculatedPlayer;
                }
                else{
                    board[y][x] = oponent;
                }
                int score = getBestMove(Board, !isCalculatedPlayer, calculatedPlayer, oponent, maxDepth - 1);
                board[y][x] = ' ';
                if(isCalculatedPlayer == true && score > bestScore){
                    bestScore = score;
                }
                else if(isCalculatedPlayer == false && score < bestScore){
                    bestScore = score;
                }

            }
        }
    }

    return bestScore;
}

void moveAi() {
    int bestScore = -infinity;
    int bestMove[2] = {0, 0};
    printAiMoves("Calculating...", messageIndex);
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (board[y][x] == ' ') {
                board[y][x] = ai;
                int score = getBestMove(board, false, ai, human, 10);
                board[y][x] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    bestMove[0] = y;
                    bestMove[1] = x;
                }
            }
        }
    }

    move(bestMove[1], bestMove[0]);

    printAiMoves(String(allCalculatedMoves), messageIndex);
    messageIndex++;
    allCalculatedMoves = 0;
    Serial.println("Move Ai stop.");
};

// Functions for drawing on the screen
void plotLineWidth(int x0, int y0, int x1, int y1, float wd, int color){ 
    int dx = abs(x1-x0), sx = x0 < x1 ? 1 : -1; 
    int dy = abs(y1-y0), sy = y0 < y1 ? 1 : -1; 
    int err = dx-dy, e2, x2, y2;
    float ed = dx+dy == 0 ? 1 : sqrt(float(dx * dx) + float(dy * dy));
    
    wd = (wd + 1) / 2;
    for(;;){
        tft.drawPixel(x0, y0, color);
        e2 = err; 
        x2 = x0;
        if(2*e2 >= -dx){
            for (e2 += dy, y2 = y0; e2 < ed*wd && (y1 != y2 || dx > dy); e2 += dx){
                tft.drawPixel(x0, y2 += sy, color);
            }
            if (x0 == x1){ 
                break;
            }
            e2 = err; 
            err -= dy; 
            x0 += sx; 
        } 
        if(2*e2 <= dy){
            for (e2 = dx-e2; e2 < ed*wd && (x1 != x2 || dx < dy); e2 += dy){
                tft.drawPixel(x2 += sx, y0, color);
            }
            if(y0 == y1){
                break;
            }
            err += dx; y0 += sy;
        }
    }
}

void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {
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

void drawCentreString(char *textBuf, int x1, int y1, int x2, int y2){
    int x = x2 / 2 + x1;
    int y = y2 / 2 + y1;
    int16_t  X, Y;
    uint16_t w, h;
    tft.getTextBounds(textBuf, x, y, &X, &Y, &w, &h);
    tft.setCursor(x - w / 2, y + h / 2);
    tft.print(textBuf);
}

void drawString(String text, int x1, int y1, int h){
    int y = y1 + h * 3/4;
    tft.setCursor(x1 + 10, y);
    tft.print(text);
}
