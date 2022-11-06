#define DEBUG  // Debug flag
#include "debug.h"
#include "wifi.h"

#define led_built_in_ESP 2
#define led_built_in_Node 16

void setup() {

  initDebugging();

  pinMode(led_built_in_ESP, OUTPUT);
  pinMode(led_built_in_Node, OUTPUT);
  digitalWrite(led_built_in_Node, HIGH);
  digitalWrite(led_built_in_ESP, HIGH);
  
  WifiConnection wifi;
  wifi.initWifi();
}

void loop() {
  blinkLed();
}

void blinkLed() {
  digitalWrite(led_built_in_Node, LOW);
  delay(2500);
  digitalWrite(led_built_in_Node, HIGH);
  delay(2500);
}