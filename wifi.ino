#include <ESP8266WiFi.h>
#include "wifi_secrets.h"

char wifiSsid[] = SECRET_WIFI_SSID;
char wifiPass[] = SECRET_WIFI_PASS;
char hostname[] = SECRET_HOSTNAME;

void initWifi() {
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