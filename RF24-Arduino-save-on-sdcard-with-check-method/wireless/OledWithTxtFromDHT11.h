/*
2018年3月16日18:31:59
DHT11使用5v供电
1106oled使用3.3v供电
注意serial.begin
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <SH1106.h>
#include <dht11.h>


// If using software SPI (the default case):
#define OLED_MOSI   11
#define OLED_CLK   8
#define OLED_DC    12
#define OLED_CS    7
#define OLED_RESET 13
#define DHT11_PIN 2
Adafruit_SH1106 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
dht11 DHT11;
/* Uncomment this block to use hardware SPI
#define OLED_DC     6
#define OLED_CS     7
#define OLED_RESET  8
Adafruit_SH1106 display(OLED_DC, OLED_RESET, OLED_CS);
*/

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SH1106_SWITCHCAPVCC);
  // init done
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  //display.display();
  //delay(2000);
  // Clear the buffer.
  //display.display();
  //delay(1000);
  display.clearDisplay();
}


void loop() {
  DHT11.read(DHT11_PIN);
  display.setTextSize(1.3);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("TEM: ");
  display.print(DHT11.temperature);
  display.println("oC");
  display.print("HUM: ");
  display.print(DHT11.humidity);
  display.println("%");
  //display.print("From_DevNum: ");
  //display.print();
  display.display();//you have to print this after any print/draw...commend
  delay(2000);
  display.clearDisplay();
  
}