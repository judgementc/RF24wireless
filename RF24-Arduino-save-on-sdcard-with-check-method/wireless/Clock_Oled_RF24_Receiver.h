/*
 *2018年3月16日18:31:59
 *miso -> 12 主机数据输入,从机信号输出 master in slave out
 *mosi -> 11 主机数据输出,从机信号输入 master out slave in
 *sck -> 13 时钟信号 serial clock
 *ss -> 10 (**RF24 not use**)随意定义 从机使能信号,由主机控制 slave select
 *ce -> 10 随意定义  SPI chip enable 使能端口,相当于ss
 *csn -> 9 随意定义 SPI chip select
 *oled模块的ISP通信是库(SH1106.h)软件定义,****所有接口都可以修改****
 *#define OLED_MOSI   4
 *#define OLED_CLK   8
 *#define OLED_DC    6
 *#define OLED_CS    7
 *#define OLED_RESET 5
 *DHT11使用5v供电
 *1106oled使用3.3v供电
 *注意serial.begin
 *DS3231时钟模块
 *SCL=SCK--> SCL 时钟线
 *SDA --> SDA 数据线
 *VCC --> 3.3v供电
 *GND --> GND
 *时钟模块在板上有专门接口 SCL 与 SDA
 */

#include<RF24.h>
#include<SPI.h>
#include <Adafruit_GFX.h>//use the oled
#include <SH1106.h>//use the oled
#include <DS3231.h>

DS3231 Clock;
bool Century=false;
bool h12;
bool PM;

RF24 radio(10,9); // ce, csn

//define the pin for Oled
#define OLED_MOSI   4
#define OLED_CLK   8
#define OLED_DC    6
#define OLED_CS    7
#define OLED_RESET 5

//actual a screen--HS1106
Adafruit_SH1106 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

//define the screen Oled Model
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

//whidth and hight
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

//显示模式
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
  
struct paket{
  byte detik = 0;
  byte menit = 0;
  byte num = 0;
  byte tem = 0;
  byte hum = 0;
};

byte detik = 0;
byte menit = 0;
byte num = 0;
byte tem = 0;
byte hum = 0;
byte alamat[][6]={"0"};

typedef struct paket paketan;
paketan Data;

void setup() {
  display.begin(SH1106_SWITCHCAPVCC);
    display.clearDisplay();
  display.clearDisplay();
  display.setTextSize(1.35);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
  display.println("PLEASE TURN ON TR!");
  display.println("POWERED BY MIKEJU");
  display.display();//you have to print this after any print/draw...commend
    delay(2000);
    display.clearDisplay();
  // put your setup code here, to run once:
  Serial.begin(115200);

  radio.begin();
  radio.setChannel(100);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1,alamat[0]);
  radio.startListening();
  Serial.print("chek done");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(radio.available()){
    while(radio.available()){
      radio.read(&Data,sizeof(Data));
      }
      Serial.print("data: ");
      Serial.print(Data.menit);
      Serial.print(":");
      Serial.println(Data.detik);
      Serial.print("from: ");
      Serial.println(Data.num);
      Serial.print("Tem: ");
      Serial.println(Data.tem);
      Serial.print("Hum: ");
      Serial.println(Data.hum);
      
    //Oled print
    display.setTextSize(1.0);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print("From: ");
    display.println(Data.num);
    display.print("Work Time: ");
    display.print(Data.menit);
    display.print(":");
    display.println(Data.detik);
    display.println("");
    display.setTextSize(2.0);
    display.setTextColor(WHITE);
    display.print(" ");
    display.print(Data.tem);
    display.print("oC");
    display.print(" ");
    //display.print("");
    display.print(Data.hum);
    display.println("%");
    //display.print();
    display.print("");
    display.print(Clock.getMonth(Century));
    display.print("-");
    display.print(Clock.getDate());
    display.print(" ");
    display.print(Clock.getHour(h12,PM));
    display.print(":");
    display.println(Clock.getMinute());
    /*
    second=Clock.getSecond();
    minute=Clock.getMinute();
    hour=Clock.getHour(h12, PM);
    date=Clock.getDate();
    month=Clock.getMonth(Century);
    year=Clock.getYear();
    */
    display.display();//you have to print this after any print/draw...commend
      delay(2000);
      display.clearDisplay();
    }
}