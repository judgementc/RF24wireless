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
#include <dht11.h>//to use the tem and hum sensor
#define DHT11_PIN 6
dht11 DHT11;
RF24 radio(10,9); // ce, csn


struct paket{
  byte detik = 0;
  byte menit = 0;
  byte num = 2;
  byte tem = 0;
  byte hum = 0;
};

byte detik = 0;
byte menit = 0;
byte tem = 0;
byte hum = 0;
byte num = 2;//you can change this value to redefine your devices 

byte alamat[][6]={"0"};

typedef struct paket paketan;
paketan Data;

void setup(){
  
  Serial.begin(115200);
  radio.begin();
  radio.setChannel(100);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);//use this to open the AP function.
  radio.openWritingPipe(alamat[0]);
  Serial.println("check done");
}

void loop(){
  radio.write(&Data,sizeof(Data));
  Serial.print("detik: ");
  Serial.println(Data.detik);
  Serial.print("menit: ");
  Serial.println(Data.menit);
  Serial.print("from: ");
  Serial.println(Data.num);
  Serial.println("Read_data_from_DHT11");
  DHT11.read(DHT11_PIN);
  Serial.print("Tem: ");
  Serial.println(DHT11.temperature);
  Serial.print("Hum: ");
  Serial.println(DHT11.humidity);
  detik++;
  Data.detik=detik;
  Data.menit=menit;
  Data.tem=DHT11.temperature;
  Data.hum=DHT11.humidity;
  delay(1000);
  if(detik>60){
    detik=0;
    menit++;
    if(menit>60){
      menit=0;
    }
  }
}