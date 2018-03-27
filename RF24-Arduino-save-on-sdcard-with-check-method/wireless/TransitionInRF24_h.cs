#include<RF24.h>
#include<SPI.h>
RF24 radio(7,8); // ce, csn

struct paket{
  byte detik = 0;
  byte menit = 0;
  byte num=1;
};

byte detik = 0;
byte menit = 0;
byte num = 1;//you can change this value to redefine your devices 

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
  detik++;
  Data.detik=detik;
  Data.menit=menit;
  delay(1000);
  if(detik>60){
    detik=0;
    menit++;
    if(menit>60){
      menit=0;
    }
    
  }
}


