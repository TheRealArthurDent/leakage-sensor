#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTION_H

#include <ESP8266WiFi.h>

class WifiConnection {

public:
  void initWifi();

private:
  void connectToWifi();
  static void onWifiConnect(const WiFiEventStationModeGotIP& event);
  static void onWifiDisconnect(const WiFiEventStationModeDisconnected& event);
};

#endif