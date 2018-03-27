/*
SD卡使用5v供电

*/
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
int second,minute,hour,date,month,year,temperature;
const int chipSelect = 46;
void setup() {
	if(!SD.begin(chipSelect))
	{
	Serial.println("initialzation falied!");
	while(1);
	}
	Serial.println("initialzation done.");
}

void loop() {
	File dataFile = SD.open("datalog.txt",FILE_WRITE);
	  if(dataFile){
  /*
  dataFile.print(DHT11.humidity);
  dataFile.print(",");
  dataFile.print(DHT11.temperature);
  dataFile.print(",");
  dataFile.print(light);
  dataFile.print(",");
  dataFile.print(year);
  dataFile.print("-");
  dataFile.print(month);
  dataFile.print("-");
  dataFile.print(date);
  dataFile.print(",");
  dataFile.print(hour);
  dataFile.print(":");
  dataFile.print(minute);
  dataFile.print(":");
  dataFile.println(second);
  */
  dataFile.println("hello!");
  dataFile.close();
  }
  else{
    Serial.println("error!");
  }
  Serial.println("wait for next datalog");
    delay(30000);
}


/*
mode2
*/
/*
SD卡使用5v供电

*/
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
int second,minute,hour,date,month,year,temperature;
const int chipSelect = 46;
void setup() {
  Serial.begin(9600);
  /*
  if(!SD.begin(chipSelect))
  {
  Serial.println("initialzation falied!");
  while(1);
  }
  Serial.println("initialzation done.");
*/
}

void loop() {
  SD.begin(chipSelect);
  Serial.println("initialzation done.");
  File dataFile = SD.open("datalog.txt",FILE_WRITE);
    if(dataFile){
  dataFile.println("hello!");
  dataFile.close();
  }
  else{
    Serial.println("error!");
  }
  Serial.println("wait for next datalog");
    delay(2000);
}