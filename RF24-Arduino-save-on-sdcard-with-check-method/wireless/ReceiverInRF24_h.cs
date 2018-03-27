/*
 *miso -> 12
 *mosi -> 11
 *sck -> 13
 *ss -> 10
 *ce -> 7
 *csn -> 8
 */
#include<RF24.h>
#include<SPI.h>
RF24 radio(7,8); // ce, csn

struct paket{
  byte detik = 0;
  byte menit = 0;
  byte num = 0;
};

byte detik = 0;
byte menit = 0;
byte num = 0;
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
    }
}