/*
 *2018年3月16日18:31:59
 *
 *uno上RF24
 *miso -> 12 主机数据输入,从机信号输出 master in slave out
 *mosi -> 11 主机数据输出,从机信号输入 master out slave in
 *sck -> 13 时钟信号 serial clock
 *ss -> 10 (**RF24 not use**)随意定义 从机使能信号,由主机控制 slave select
 *ce -> 10 随意定义  SPI chip enable 使能端口,相当于ss
 *csn -> 9 随意定义 SPI chip select

 *mega上RF24 供电5v
 *miso -> 51
 *mosi -> 50 
 *sck -> 52
 *ce -> 48
 *csn -> 49

 *oled模块 无需供电(mega and uno)的ISP通信是库(SH1106.h)软件定义,****所有接口都可以修改****
 *#define OLED_MOSI   7
 *#define OLED_CLK   8
 *#define OLED_DC    5
 *#define OLED_CS    4
 *#define OLED_RESET 6

 *注意serial.begin

 *DS3231时钟模块 3.3v
 *SCL=SCK--> SCL 时钟线
 *SDA --> SDA 数据线
 *VCC --> 3.3v供电
 *GND --> GND
 *时钟模块在板上有专门接口 SCL 与 SDA
 
 *DHT11使用5v供电
 *1106oled使用3.3v供电
 *3231时钟使用3.3v供电
 *RF24(带AP与voltage regulator)使用5v供电
 *SD卡模块 5v 供电
 *光照传感器使用5v供电
 *土壤湿度传感器使用3.3供电
 *土壤湿度传感器还具备数字电平输出(阈值)功能

 *SD卡片选cs
 *CS -> 46

 *注意serial与spi冲突,上传完成后需要关闭Serial串口重启
 *SDcard.begain(chipSelectPin)
 *注意为loop中个步骤设置检查check(if/else条件,并在oled输出)
 */

#include<RF24.h>
#include<SPI.h>
#include <Adafruit_GFX.h>//use the oled
#include <SH1106.h>//use the oled
#include <DS3231.h>
#include <dht11.h>

//SDcard
#include <SD.h>
#include <Wire.h>

DS3231 Clock;
bool Century=false;
bool h12;
bool PM;

//sdcard
const int chipSelect = 46;

RF24 radio(48,49); // ce, csn

//define the pin for Oled
#define OLED_MOSI   7
#define OLED_CLK   8
#define OLED_DC    5
#define OLED_CS    4
#define OLED_RESET 6

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

//dht sensor
#define DHT11_PIN 47
dht11 DHT11;

//light
int Light=0;


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
  int light = 0;
  int smoi = 0;
};

byte detik = 0;
byte menit = 0;
byte num = 0;
byte tem = 0;
byte hum = 0;
int light = 0;
int smoi = 0;

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
  //Serial.begin(115200);此处由于串口与spi冲突,不使用串口与电脑通信

    if(!radio.begin()){
    display.setTextSize(1.0);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Please make sure the RF24/Clock module has been connected properlly");
    display.display();//you have to print this after any print/draw...commend
        delay(5000);
        display.clearDisplay();
  }
  radio.setChannel(100);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1,alamat[0]);
  radio.startListening();

  Serial.print("chek done");
}

void loop() {
  int lightm;
  // put your main code here, to run repeatedly:
  DHT11.read(DHT11_PIN);
  lightm=analogRead(Light);
  int lightmb=lightm*(-6.6762)+1232.2;
  if(radio.available()){
    while(radio.available()){
      radio.read(&Data,sizeof(Data));
      }
     
  //SDcard,由于与Serial串口冲突,所有提示在Oled上完成
  SD.begin(chipSelect);
    File dataFile = SD.open("datalog.txt",FILE_WRITE);
    if(dataFile){
//from the master itself
  dataFile.print("1");
    dataFile.print(",");
    dataFile.print(DHT11.temperature);
    dataFile.print(",");
    dataFile.print(DHT11.humidity);
    dataFile.print(",");
  dataFile.print(lightmb);
  dataFile.print(",");
    dataFile.print(Clock.getMonth(Century));
    dataFile.print("-");
    dataFile.print(Clock.getDate());
    dataFile.print(",");
    dataFile.print(Clock.getHour(h12,PM));
    dataFile.print("-");
    dataFile.println(Clock.getMinute());
  delay(70);
//from the rf24 massage
  dataFile.print(Data.num);
    dataFile.print(",");
    dataFile.print(Data.tem);
    dataFile.print(",");
    dataFile.print(Data.hum);
    dataFile.print(",");
    dataFile.print(Data.light);
    dataFile.print(",");
    dataFile.print(Data.smoi);
    dataFile.print(",");
    dataFile.print(Clock.getMonth(Century));
    dataFile.print("-");
    dataFile.print(Clock.getDate());
    dataFile.print(",");
    dataFile.print(Clock.getHour(h12,PM));
    dataFile.print("-");
    dataFile.println(Clock.getMinute());
    dataFile.close();
    }
  //SD卡未插提示
    else{
    display.setTextSize(1.0);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("NO SDcard Loaded!");
    display.display();//you have to print this after any print/draw...commend
        delay(200000);
        display.clearDisplay();
    }

    //Oled print
    display.setTextSize(1.0);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
  
  display.print("From: ");
    display.println("master");
  display.println("");
    //display.print("Work Time: ");
    //display.print(Data.menit);
    //display.print(":");
    //display.println(Data.detik);
    display.print(Clock.getMonth(Century));
    display.print("-");
    display.print(Clock.getDate());
    display.print(" ");
    display.print(Clock.getHour(h12,PM));
    display.print(":");
    display.println(Clock.getMinute());
    display.println("");
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print(" ");
    display.print(DHT11.temperature);
    display.print("oC");
    display.print(" ");
    display.print(DHT11.humidity);
    display.println("%");
  display.print(" L: ");
  display.println(lightmb);

  display.display();
  delay(2000);
  display.clearDisplay();
    /*
  display.print(" ");
    display.print("L");
    display.print(Data.light);
    display.print(" ");
    display.print("S");
    display.print(Data.smoi);
  */

//rf24
  display.setCursor(0,0);
    display.setTextSize(1.0);
    display.setTextColor(WHITE);
    display.print("From: ");
    display.println(Data.num);
    display.print("Work Time: ");
    display.print(Data.menit);
    display.print(":");
    display.println(Data.detik);
    
    display.print(Clock.getMonth(Century));
    display.print("-");
    display.print(Clock.getDate());
    display.print(" ");
    display.print(Clock.getHour(h12,PM));
    display.print(":");
    display.println(Clock.getMinute());
    
    display.println("");
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print(" ");
    display.print(Data.tem);
    display.print("oC");
    display.print(" ");
    display.print(Data.hum);
    display.println("%");
    display.print(" ");
    display.print("L");
    display.print(Data.light);
    display.print(" ");
    display.print("S");
    display.print(Data.smoi);
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