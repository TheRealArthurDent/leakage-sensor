#include "wifi.h"
#include <Ticker.h>
#include "wifi_secrets.h"

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
Ticker wifiReconnectTimer;

char wifiSsid[] = SECRET_WIFI_SSID;
char wifiPass[] = SECRET_WIFI_PASS;
char hostname[] = SECRET_HOSTNAME;

void WifiConnection::initWifi() {
  DEBUG_PRINT("Connecting to ");
  DEBUG_PRINTLN(wifiSsid);

  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostname);
  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);
  connectToWifi();
}

void WifiConnection::connectToWifi() {

  WiFi.begin(wifiSsid, wifiPass);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(led_built_in_ESP, LOW);
    delay(250);
    digitalWrite(led_built_in_ESP, HIGH);
    delay(250);
    DEBUG_PRINT(".");
  }
}

void WifiConnection::onWifiConnect(const WiFiEventStationModeGotIP& event) {
  DEBUG_PRINT("Connected to WiFi ");
  DEBUG_PRINTLN(wifiSsid);
  DEBUG_PRINT("IP address: ");
  DEBUG_PRINTLN(WiFi.localIP());
}

void WifiConnection::onWifiDisconnect(const WiFiEventStationModeDisconnected& event) {
  DEBUG_PRINTLN("Disconnected from WiFi ");
  DEBUG_PRINTLN(wifiSsid);
  // Apparently this is not even required, since ESP8266WiFiClass tries to reconnect like a mad man anyway.
  // wifiReconnectTimer.once(2, connectToWifi);
}