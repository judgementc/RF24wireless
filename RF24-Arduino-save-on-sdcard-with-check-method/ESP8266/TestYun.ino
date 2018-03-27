#include <TaskScheduler.h>
#include <PubSubClient.h>
#include <BridgeClient.h>
#include <Bridge.h>
#include <Arduino.h>

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

BridgeClient client;
PubSubClient mqttclient {IOT_ENDPOINT, 1883, mqtt_callback, client};

void ticker_handler() {
  if (!mqttclient.connected()) {
    Serial.println(F("Connecting to MQTT broker."));
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

void setup() {
  Bridge.begin();
  Serial.begin(74880);
  while (!Serial);
  randomSeed(analogRead(0));
  Serial.println(F("Arduino Yun starts."));
  
  runner.init();
  runner.addTask(schedule_task);
  schedule_task.enable();
}

void loop() {
  mqttclient.loop();
  runner.execute();
}
