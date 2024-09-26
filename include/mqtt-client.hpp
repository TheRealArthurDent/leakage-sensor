#pragma once

#include "wifi-dependent.hpp"
#include <AsyncMqttClient.hpp>
#include <Ticker.h>
#include <string>

/**
 * <a href="https://www.hivemq.com/blog/mqtt-essentials-part-6-mqtt-quality-of-service-levels/">
 * Quality of service</a> enum for MQTT messaging.
 */
enum Qos
{
  /// @brief QoS - At most once.
  AT_MOST_ONCE = 0,
  /// @brief QoS - At least once.
  AT_LEAST_ONCE = 1,
  /// @brief QoS - Exactly once.
  EXACTLY_ONCE = 2,
};

/**
 * \brief A very basic MQTT client.
 *
 * This fella just showcases the use of marvinroger's
 * <a href="https://github.com/marvinroger/async-mqtt-client">Async MQTT
 * client for ESP8266 and ESP32</a>.
 * Extend it to build more sophisticated stuff.
 */
class MqttClient : public WifiDependent
{
private:
  bool connected = false;
  AsyncMqttClient mqttClient;
  Ticker mqttReconnectTimer;

  std::string TOPIC_BASE = "subscribers/";
  std::string TOPIC_CONNECTION_STATUS = "/connection-status";
  std::string connectionStatusTopic;

public:
  MqttClient() : mqttClient(AsyncMqttClient()),
                 mqttReconnectTimer(Ticker()),
                 connectionStatusTopic(TOPIC_BASE + SECRET_HOSTNAME + TOPIC_CONNECTION_STATUS){};
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
   * ESP8266WiFi in \c WiFiConnection will try to reconnect itself, so no need
   * to handle this within this controller.
   */
  void onWifiConnectionLost() override;

  /**
   * Returns whether the client is connected to the specified MQTT broker.
   */
  auto isConnected() -> bool;

  /**
   * Publishes a payload to the specified topic.
   *
   * \param topic The MQTT topic to publish the content to.
   * \param payload The content to publish.
   * \param qos <a href="https://www.hivemq.com/blog/mqtt-essentials-part-6-mqtt-quality-of-service-levels/">
   * MQTT's Quality of service level</a> .
   * \param retain <a href="https://www.hivemq.com/blog/mqtt-essentials-part-8-retained-messages/">
   * MQTT's retain flag</a>.
   *
   * \returns \c true if the message was successfully published, otherwise \c false.
   */
  auto publish(std::string topic, std::string payload, Qos qos = AT_LEAST_ONCE, bool retain = false) -> bool;

private:
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
