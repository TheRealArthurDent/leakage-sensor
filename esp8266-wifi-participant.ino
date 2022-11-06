#include <ESP8266WiFi.h>
#include "wifi_secrets.h"


#define led_built_in_ESP 2
#define led_built_in_Node 16

char wifiSsid[] = SECRET_WIFI_SSID;
char wifiPass[] = SECRET_WIFI_PASS;

void setup() {

  Serial.begin(115200);

  pinMode(led_built_in_ESP, OUTPUT);
  pinMode(led_built_in_Node, OUTPUT);
  digitalWrite(led_built_in_Node, HIGH);
  digitalWrite(led_built_in_ESP, HIGH);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifiSsid);

  WiFi.mode(WIFI_STA);
  WiFi.hostname("TestParticipant");
  WiFi.begin(wifiSsid, wifiPass);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(led_built_in_ESP, LOW);
    delay(250);
    digitalWrite(led_built_in_ESP, HIGH);
    delay(250);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
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