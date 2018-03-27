#include <dht11.h>
#define DHT11_PIN 2
dht11 DHT11;
void setup(){
  Serial.begin(9600);
}

void loop(){
  DHT11.read(DHT11_PIN);
  Serial.print("Tem: ");
  Serial.println(DHT11.temperature);
  Serial.print("Hum: ");
  Serial.println(DHT11.humidity);
  delay(2000);
}
