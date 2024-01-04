#include <Arduino.h>

#include "main.hpp"
#include "led.h"
#include "debug.h"
#include "wifi-connection.hpp"
#include "ota-handler.hpp"
#include "mqtt-client.hpp"
#include "metronome.hpp"
#include "water-sensor.hpp"

const int LOOP_DURATION = 10000;

const int THRESHOLD_WATERSENSOR_1 = 50;
const int THRESHOLD_WATERSENSOR_2 = 20;

const int BUZZER = D5;

Metronome metronome(LOOP_DURATION);

MqttClient myMqttClient;

WaterSensor waterSensor1(A0, D1);
WaterSensor waterSensor2(A0, D2);

// cppcheck-suppress unusedFunction
void setup()
{
  initDebugging();

  // buzzer
  pinMode(BUZZER, OUTPUT);

  // MqttClient mqttClient;
  myMqttClient.init();

  std::list<WifiDependent *> deps;
  deps.push_back(&OtaHandler::getInstance());
  deps.push_back(&myMqttClient);

  WifiConnection::getInstance().init(deps);
}

// cppcheck-suppress unusedFunction
void loop()
{
  char channel[80];
  char buffer[5];
  // D3
  int level1 = waterSensor1.getLevel();
  strcpy(channel, "WaterLevel1");
  DEBUG_PRINT(channel);
  DEBUG_PRINT(": ");
  DEBUG_PRINT(level1);
  DEBUG_PRINT(" (");
  sprintf(buffer, "%d", level1);
  DEBUG_PRINT(buffer);
  DEBUG_PRINTLN(")");
  myMqttClient.publish(channel, buffer);

  int level2 = waterSensor2.getLevel();
  strcpy(channel, "WaterLevel2");
  DEBUG_PRINT(channel);
  DEBUG_PRINT(": ");
  DEBUG_PRINT(level2);
  DEBUG_PRINT(" (");
  sprintf(buffer, "%d", level2);
  DEBUG_PRINT(buffer);
  DEBUG_PRINTLN(")");
  myMqttClient.publish(channel, buffer);

  // alert?
  if (level1 > THRESHOLD_WATERSENSOR_1 || level2 > THRESHOLD_WATERSENSOR_2)
  {
    digitalWrite(BUZZER, HIGH);
    delay(2000);
    digitalWrite(BUZZER, LOW);
  }

  metronome.waitForNextCycle();
  OtaHandler::getInstance().handleUpload();
}
