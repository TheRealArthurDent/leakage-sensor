#include <ESP8266WiFi.h>
#include "wifi_secrets.h"

#define DEBUG // Debug flag

#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#endif

#define led_built_in_ESP 2
#define led_built_in_Node 16

char wifiSsid[] = SECRET_WIFI_SSID;
char wifiPass[] = SECRET_WIFI_PASS;
char hostname[] = SECRET_HOSTNAME;

void setup() {

  #ifdef DEBUG
    Serial.begin(115200);
  #endif

  pinMode(led_built_in_ESP, OUTPUT);
  pinMode(led_built_in_Node, OUTPUT);
  digitalWrite(led_built_in_Node, HIGH);
  digitalWrite(led_built_in_ESP, HIGH);

  DEBUG_PRINTLN();
  DEBUG_PRINTLN();
  DEBUG_PRINT("Connecting to ");
  DEBUG_PRINTLN(wifiSsid);

  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostname);
  WiFi.begin(wifiSsid, wifiPass);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(led_built_in_ESP, LOW);
    delay(250);
    digitalWrite(led_built_in_ESP, HIGH);
    delay(250);
    DEBUG_PRINT(".");
  }

  DEBUG_PRINTLN("");
  DEBUG_PRINTLN("WiFi connected");
  DEBUG_PRINTLN("IP address: ");
  DEBUG_PRINTLN(WiFi.localIP());
}

void loop() {
  blinkLed();
}

void blinkLed() {
  digitalWrite(led_built_in_Node, LOW);
  delay(2000);
  digitalWrite(led_built_in_Node, HIGH);
  delay(2000);
}