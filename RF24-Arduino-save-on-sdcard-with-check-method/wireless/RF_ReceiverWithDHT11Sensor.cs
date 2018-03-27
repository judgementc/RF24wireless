/*
 *miso -> 12 主机数据输入,从机信号输出 master in slave out
 *mosi -> 11 主机数据输出,从机信号输入 master out slave in
 *sck -> 13 时钟信号 serial clock
 *ss -> 10 (**RF24 not use**)随意定义 从机使能信号,由主机控制 slave select
 *ce -> 10 随意定义  SPI chip enable 使能端口,相当于ss
 *csn -> 9 随意定义 SPI chip select
 *oled模块的ISP通信是库(SH1106.h)软件定义,所有接口都可以修改
 *2018年3月16日18:31:59
 *DHT11使用5v供电
 *1106oled使用3.3v供电
 *注意serial.begin
 */

#include<RF24.h>
#include<SPI.h>
#include <Adafruit_GFX.h>//use the oled
#include <SH1106.h>//use the oled
RF24 radio(10,9); // ce, csn

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
    }
}