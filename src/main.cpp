#include "Arduino.h"

#include "main.hpp"
#include "led.h"
#include "debug.h"
#include "wifi-connection.hpp"
#include "ota-handler.hpp"
#include "mqtt-client.hpp"
#include "metronom.hpp"
#include "water-sensor.hpp"

const int LOOP_DURATION = 10000;

const int THRESHOLD_WATERSENSOR_1 = 150; // 500
const int THRESHOLD_WATERSENSOR_2 = 120; // 200

const int BUZZER = D5;

const int BUTTON = D6;

const int RGB_LED_GREEN = D7;
const int RGB_LED_RED = D8;

Metronom metronom(LOOP_DURATION);

MqttClient myMqttClient;

WaterSensor waterSensor1(A0, D1);
WaterSensor waterSensor2(A0, D2);

volatile int counter = 0;

void IRAM_ATTR isr_buttonPressed()
{
  counter++;
}

// cppcheck-suppress unusedFunction
void setup()
{
  initDebugging();

  // buzzer
  pinMode(BUZZER, OUTPUT);

  // button
  pinMode(BUTTON, INPUT_PULLUP);

  pinMode(RGB_LED_GREEN, OUTPUT);
  pinMode(RGB_LED_RED, OUTPUT);

  // MqttClient mqttClient;
  myMqttClient.init();

  std::list<WifiDependent *> deps;
  deps.push_back(&OtaHandler::getInstance());
  deps.push_back(&myMqttClient);

  WifiConnection::getInstance().init(deps);

  attachInterrupt(digitalPinToInterrupt(BUTTON), isr_buttonPressed, FALLING);
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

  strcpy(channel, "Counter");
  DEBUG_PRINT(channel);
  DEBUG_PRINT(": ");
  DEBUG_PRINT(counter);
  DEBUG_PRINT(" (");
  sprintf(buffer, "%d", counter);
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

  DEBUG_PRINT("Counter: ");
  DEBUG_PRINTLN(counter);
  if (counter % 4 == 0)
  {
    analogWrite(RGB_LED_GREEN, 0);
    analogWrite(RGB_LED_RED, 0);
  }
  else if (counter % 4 == 1)
  {
    analogWrite(RGB_LED_GREEN, 0);
    analogWrite(RGB_LED_RED, 150);
  }
  else if (counter % 4 == 2)
  {
    analogWrite(RGB_LED_GREEN, 150);
    analogWrite(RGB_LED_RED, 0);
  }
  else
  {
    // yellow
    analogWrite(RGB_LED_GREEN, 100);
    analogWrite(RGB_LED_RED, 100);
  }

  metronom.waitForNextCycle();
  OtaHandler::getInstance().handleUpload();
}
