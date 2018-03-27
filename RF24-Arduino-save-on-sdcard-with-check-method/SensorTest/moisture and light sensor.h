/*
光照传感器使用5v供电
土壤湿度传感器使用3.3供电
土壤湿度传感器还具备数字电平输出(阈值)功能
*/

#define Light 1
#define SMoisture 0
#include <dht11.h>
#define DHT11_PIN 8 
dht11 DHT11;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600); 
}

void loop() {
  int light;
  int smoi;
  light=analogRead(Light);
  smoi=analogRead(SMoisture);
  DHT11.read(DHT11_PIN);
  Serial.print("Light: ");
  Serial.println(light);
  Serial.print("SMoisture: ");
  Serial.println(smoi);
  Serial.print("TEM: ");
  Serial.println(DHT11.temperature);
  Serial.print("HUM: ");
  Serial.println(DHT11.humidity);
  delay(5000);
  // put your main code here, to run repeatedly:

}