#include <TaskScheduler.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <Arduino.h>

const char* WIFI_SSID     = "iot";
const char* WIFI_PASSWORD = "iot123456";

const char* IOT_ENDPOINT  = "iotfreetest.mqtt.iot.gz.baidubce.com";
const char* IOT_USERNAME  = "iotfreetest/thing01";
const char* IOT_KEY       = "YU7Tov8zFW+WuaLx9s9I3MKyclie9SGDuuNkl6o9LXo=";
const char* IOT_TOPIC     = "demoTopic";
const char* IOT_CLIENT_ID = "iot_demo_d_";

void mqtt_callback (char* topic, byte* payload, unsigned int length) {
  byte *end = payload + length;
  for (byte *p = payload; p < end; ++p) {
    Serial.print(*((const char *)p));
  }
  Serial.println("");
}

WiFiClientSecure client;
PubSubClient mqttclient(IOT_ENDPOINT, 1884, &mqtt_callback, client);

void ticker_handler() {
  if (!mqttclient.connected()) {
    Serial.print(F("MQTT state: "));
    Serial.println(mqttclient.state());
    String clientid {IOT_CLIENT_ID + String{random(10000)}};
    if (mqttclient.connect(clientid.c_str(), IOT_USERNAME, IOT_KEY)) {
      Serial.print(F("MQTT Connected. Client id = "));
      Serial.println(clientid.c_str());
      mqttclient.subscribe(IOT_TOPIC);
    }
  } else {
    static int counter = 0;
    String buffer {"MQTT message from Arduino: " + String{counter++}};
    mqttclient.publish(IOT_TOPIC, buffer.c_str());
  }
}

Task schedule_task(5000, TASK_FOREVER, &ticker_handler);
Scheduler runner;

void connect_wifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("\nWiFi connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(74880);
  while (!Serial);
  randomSeed(analogRead(0));

  connect_wifi();

  runner.init();
  runner.addTask(schedule_task);
  schedule_task.enable();
}

void loop() {
  mqttclient.loop();
  runner.execute();
}
