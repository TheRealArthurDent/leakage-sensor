#pragma once

#include <AsyncMqttClient.h>
#include "wifi-dependent.hpp"

class MqttClient : public WifiDependent
{
public:
  void init();
  void onWifiConnectionEstablished() override;
  void onWifiConnectionLost() override;

private:
  char *connectionStatusTopic;

  void connect();
  void onConnect(boolean sessionPresent);
  void onDisconnect(AsyncMqttClientDisconnectReason reason);
  void onMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);
};
