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
float iv = .1;
float x1, y1;
float x2, y2;

void setup(void) {
  Serial.begin(9600);
  Serial.println("Running design2 program.");
  tft.begin(0X9327);//to enable ILI9327 driver code
}

void loop(void) {
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
  delay(1000);
  iv += .1;
}
