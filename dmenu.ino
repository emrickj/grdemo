// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.
//by Open-Smart Team and Catalex Team
//catalex_inc@163.com
//Store:   http://dx.com
//           https://open-smart.aliexpress.com/store/1199788
//Demo Function: Display graphics, characters
//Arduino IDE: 1.6.5
// Board: Arduino UNO R3, Arduino Mega2560,Arduino Leonardo

// Board:OPEN-SMART UNO R3 5V / 3.3V, Arduino UNO R3, Arduino Mega2560
//3.2INCH TFT:
// https://www.aliexpress.com/store/product/3-2-TFT-LCD-Display-module-Touch-Screen-Shield-board-onboard-temperature-sensor-w-Touch-Pen/1199788_32755473754.html?spm=2114.12010615.0.0.bXDdc3
//OPEN-SMART UNO R3 5V / 3.3V:
// https://www.aliexpress.com/store/product/OPEN-SMART-5V-3-3V-Compatible-UNO-R3-CH340G-ATMEGA328P-Development-Board-with-USB-Cable-for/1199788_32758607490.html?spm=2114.12010615.0.0.ckMTaN


#include <Adafruit_GFX.h>    // Core graphics library
//#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>

//***********************************************//
// If you use OPEN-SMART TFT breakout board                 //
// Reconmmend you to add 5V-3.3V level converting circuit.
// Of course you can use OPEN-SMART UNO Black version with 5V/3.3V power switch,
// you just need switch to 3.3V.
// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
//----------------------------------------|
// TFT Breakout  -- Arduino UNO / Mega2560 / OPEN-SMART UNO Black
// GND              -- GND
// 3V3               -- 3.3V
// CS                 -- A3
// RS                 -- A2
// WR                -- A1
// RD                 -- A0
// RST                -- RESET
// LED                -- GND
// DB0                -- 8
// DB1                -- 9
// DB2                -- 10
// DB3                -- 11
// DB4                -- 4
// DB5                -- 13
// DB6                -- 6
// DB7                -- 7

uint8_t YP = A1;  // must be an analog pin, use "An" notation!
uint8_t XM = A2;  // must be an analog pin, use "An" notation!
uint8_t YM = 7;   // can be a digital pin
uint8_t XP = 6;   // can be a digital pin
uint8_t SwapXY = 0;

uint16_t TS_LEFT = 920;
uint16_t TS_RT  = 180;
uint16_t TS_TOP = 960;
uint16_t TS_BOT = 180;
char *name = "Unknown controller";

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 500);
TSPoint tp;
Adafruit_GFX_Button opt1,opt2,opt3,opt4,opt5;

#define MINPRESSURE 100
#define MAXPRESSURE 6000

#define SWAP(a, b) {uint16_t tmp = a; a = b; b = tmp;}

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;
int cx = tft.width() / 2;
int cy = tft.height() / 2;
int w = tft.width();
float iv = 1.8;
float x1, y1;
float x2, y2;

void setup(void) {
  Serial.begin(9600);
  Serial.println("Running GRMENU program.");
  tft.begin(0X9327);//to enable ILI9327 driver code
}

void design1(void){
  int j;
  float x3 = 0.0;
  float y3 = 0.0;
  x2 = cx;
  y2 = cy;
  tft.fillScreen(BLACK);
  for(j=0;j<200;j++) {
    x1 = x2;
    y1 = y2;
    x2 = cx + (sin(x3) * (x3 / 2));
    y2 = cy + (cos(y3) * (y3 / 2));
    tft.drawLine(x1, y1, x2, y2, WHITE);
    x3 += iv;
    y3 += iv;
  }
  while (1) {
    digitalWrite(A3,HIGH);
    tp = ts.getPoint();   //tp.x, tp.y are ADC values
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    pinMode(XP, OUTPUT);
    pinMode(YM, OUTPUT);
    if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) break;
  }
}

void design2(void) {
  while (1) {
    int j;
    float x3 = 0.0;
    float y3 = 0.0;
    x2 = cx;
    y2 = cy;
    tft.fillScreen(BLACK);
    for(j=0;j<200;j++) {
      x1 = x2;
      y1 = y2;
      x2 = cx + (sin(x3) * (x3 / iv));
      y2 = cy + (cos(y3) * (y3 / iv));
      if (j & 1) tft.drawLine(x1, y1, x2, y2, BLUE);
         else tft.drawLine(x1, y1, x2, y2, GREEN);
      x3 += iv;
      y3 += iv;
    }
    //delay(1000);
    for (j=0;j<1000;j++) {
      digitalWrite(A3,HIGH);
      tp = ts.getPoint();   //tp.x, tp.y are ADC values
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      pinMode(XP, OUTPUT);
      pinMode(YM, OUTPUT);
      if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) break;
    }
    if (j==1000) iv += .1; else break;
  }
}

void design3(void) {
  int j,k;
  tft.fillScreen(BLACK);
  for(j=0;j<3;j++) {
    for(k=0;k<64;k++)
       tft.drawLine(1,k+(j*128)+1,w,k+(j*128)+1,k<<5);
    for(k=0;k<64;k++)
       tft.drawLine(1,k+(j*128)+65,w,k+(j*128)+65,0x7E0-(k<<5));
  }
  while (1) {
    digitalWrite(A3,HIGH);
    tp = ts.getPoint();   //tp.x, tp.y are ADC values
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    pinMode(XP, OUTPUT);
    pinMode(YM, OUTPUT);
    if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) break;
  }
}

void design4(void) {
  int j, x;
  int y;
  tft.fillScreen(BLACK);
  for(j=0;j<3;j++) {
    for(x=0;x<64;x++) {
       y = sqrt(4096 - pow(x, 2)) - 1;
       tft.drawLine(1,63-x+(j*128),w,63-x+(j*128),y<<5);
    }
    for(x=0;x<64;x++) {
       y = sqrt(4096 - pow(x, 2)) - 1;
       tft.drawLine(1,64+x+(j*128),w,64+x+(j*128),y<<5);
    }
  }
  while (1) {
    digitalWrite(A3,HIGH);
    tp = ts.getPoint();   //tp.x, tp.y are ADC values
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    pinMode(XP, OUTPUT);
    pinMode(YM, OUTPUT);
    if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) break;
  }
}

void design5(void) {
  int j;
  tft.fillScreen(BLACK);
  for(j=0;j<32;j++) tft.drawLine(0, j, w, j, tft.color565(0,0,j<<3));
  for(j=0;j<32;j++) tft.drawLine(0, j+32, w, j+32, tft.color565(0,j<<3,248-(j<<3)));
  for(j=0;j<32;j++) tft.drawLine(0, j+64, w, j+64, tft.color565(0,248,j<<3));
  for(j=0;j<32;j++) tft.drawLine(0, j+96, w, j+96, tft.color565(j<<3,248-(j<<3),248-(j<<3)));
  for(j=0;j<32;j++) tft.drawLine(0, j+128, w, j+128, tft.color565(248,0,j<<3));
  for(j=0;j<32;j++) tft.drawLine(0, j+160, w, j+160, tft.color565(248,j<<3,248-(j<<3)));
  for(j=0;j<32;j++) tft.drawLine(0, j+192, w, j+192, tft.color565(248,248,j<<3));
  for(j=0;j<32;j++) tft.drawLine(0, j+224, w, j+224, tft.color565(248-(j<<3),248-(j<<3),248-(j<<3)));
  while (1) {
    digitalWrite(A3,HIGH);
    tp = ts.getPoint();   //tp.x, tp.y are ADC values
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    pinMode(XP, OUTPUT);
    pinMode(YM, OUTPUT);
    if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) break;
  }
}

void loop(void) {
  uint16_t xpos, ypos;  //screen coordinates
  tft.fillScreen(BLACK);
  opt1.initButton(&tft,  cx, 32, w-4, 60, WHITE, BLUE, BLACK, "Design 1", 4);
  opt1.drawButton(false);
  opt2.initButton(&tft,  cx, 96, w-4, 60, WHITE, RED, BLACK, "Design 2", 4);
  opt2.drawButton(false);
  opt3.initButton(&tft,  cx, 160, w-4, 60, WHITE, GREEN, BLACK, "Design 3", 4);
  opt3.drawButton(false);
  opt4.initButton(&tft,  cx, 224, w-4, 60, WHITE, CYAN, BLACK, "Design 4", 4);
  opt4.drawButton(false);
  opt5.initButton(&tft,  cx, 288, w-4, 60, WHITE, MAGENTA, BLACK, "Design 5", 4);
  opt5.drawButton(false);
  while (1) {
    digitalWrite(A3,HIGH);
    tp = ts.getPoint();   //tp.x, tp.y are ADC values
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    pinMode(XP, OUTPUT);
    pinMode(YM, OUTPUT);
    if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
        xpos = map(tp.x, TS_LEFT, TS_RT, 0, tft.width());
        ypos = map(tp.y, TS_TOP, TS_BOT, 0, tft.height());
        if (ypos>0 && ypos<80) {
          design1();
          break;
        }
        if (opt2.contains(xpos,ypos)) {
          design2();
          break;
        }
        if (opt3.contains(xpos,ypos)) {
          design3();
          break;
        }
        if (opt4.contains(xpos,ypos)) {
          design4();
          break;
        }
        if (opt5.contains(xpos,ypos)) {
          design5();
          break;
        }
    }
  }
}
