#pragma once

#include "wifi-dependent.hpp"

/**
 * \brief A very basic MQTT client.
 *
 * This fella just showcases the use of marvinroger's
 * <a href="https://github.com/marvinroger/async-mqtt-client">Async MQTT
 * client for ESP8266 and ESP32</a>.
 * Extend it to build more sophistcated stuff.
 */
class MqttClient : public WifiDependent
{

public:
  /**
   * Initializes the async-mqtt-client.
   */
  void init();
  /**
   * This method will be called by \c WiFiConnection once a network connection
   * has been established. It will then try to connect to the configured MQTT
   * broker using marvinroger's
   * <a href="https://github.com/marvinroger/async-mqtt-client">Async MQTT
   * client for ESP8266 and ESP32</a>.
   */
  void onWifiConnectionEstablished() override;
  /**
   * This method will just log that it has been disconnected.
   * The async-mqtt-client will try to reconnect itself, so no need to handle
   * this withing this controller.
   */
  void onWifiConnectionLost() override;

private:
  char *connectionStatusTopic;

  void connect();
  /**
   * Is called by async-mqtt-client once a connection to the MQTT
   * broker has been established.
   * It will publish a connection status CONNECTED and also leave a
   * (last)will, pulling its conntecion status to DISCONNECTED.
   * After that it will subscribe to a certain topic.
   */
  void onConnect(boolean sessionPresent);
  void onDisconnect(AsyncMqttClientDisconnectReason reason);
  /**
   * Is called by async-mqtt-client once a message has been received.
   * It will log the message and publish a message via /lastReceived.
   */
  void onMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);
};
