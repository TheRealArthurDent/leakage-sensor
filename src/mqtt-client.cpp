#include "mqtt-client.hpp"
#include "debug.h"
#include "wifi-connection.hpp"
#include <AsyncMqttClient.hpp>
#include <Ticker.h>

AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;

void MqttClient::init()
{
  connectionStatusTopic = TOPIC_BASE + SECRET_HOSTNAME + TOPIC_CONNECTION_STATUS;

  mqttClient.setWill(connectionStatusTopic.c_str(), AT_LEAST_ONCE, true, "DISCONNECTED");

  // mqttClient.onConnect(onConnect);
  mqttClient.onConnect([this](bool sessionPresent)
                       { onConnect(sessionPresent); });
  // mqttClient.onDisconnect(onDisconnect);
  mqttClient.onDisconnect([this](AsyncMqttClientDisconnectReason reason)
                          { onDisconnect(reason); });
  // mqttClient.onSubscribe(onMqttSubscribe);
  // mqttClient.onUnsubscribe(onMqttUnsubscribe);
  // mqttClient.onMessage(onMqttMessage);
  mqttClient.onMessage([this](char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
                       { onMessage(topic, payload, properties, len, index, total); });
  // mqttClient.onPublish(onMqttPublish);
  mqttClient.setCredentials(SECRET_MQTT_USER, SECRET_MQTT_PASSWD);
  mqttClient.setServer(SECRET_MQTT_HOST, SECRET_MQTT_PORT);
}

void MqttClient::connect()
{
  DEBUG_PRINTLN("Connecting to MQTT broker...");
  mqttClient.connect();
}

// cppcheck-suppress unusedFunction
// used by void WifiConnection::notifyDependentsConnected()
void MqttClient::onWifiConnectionEstablished()
{
  DEBUG_PRINTLN("WiFi connected!");

  connect();
}

// cppcheck-suppress unusedFunction
// used by void WifiConnection::notifyDependentsDisconnected()
void MqttClient::onWifiConnectionLost()
{
  DEBUG_PRINTLN("WiFi disconnected!");
}

void MqttClient::onConnect(bool sessionPresent)
{
  DEBUG_PRINT("Connected to MQTT. ");
  DEBUG_PRINT("Session present: ");
  DEBUG_PRINTLN(sessionPresent);

  mqttClient.publish(connectionStatusTopic.c_str(), AT_LEAST_ONCE, true, "CONNECTED");
}

void MqttClient::onDisconnect(AsyncMqttClientDisconnectReason reason)
{
  DEBUG_PRINTLN("Disconnected from MQTT.");

  if (WifiConnection::getInstance().isConnected())
  {
    // mqttReconnectTimer.once(2, connect);
    mqttReconnectTimer.once(
        2, +[](MqttClient *client)
           { client->connect(); },
        this);
  }
}

void MqttClient::onMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
  DEBUG_PRINTLN("Publish received.");
  DEBUG_PRINT("  topic: ");
  DEBUG_PRINTLN(topic);
  DEBUG_PRINT("  qos: ");
  DEBUG_PRINTLN(properties.qos);
  DEBUG_PRINT("  dup: ");
  DEBUG_PRINTLN(properties.dup);
  DEBUG_PRINT("  retain: ");
  DEBUG_PRINTLN(properties.retain);
  DEBUG_PRINT("  len: ");
  DEBUG_PRINTLN(len);
  DEBUG_PRINT("  index: ");
  DEBUG_PRINTLN(index);
  DEBUG_PRINT("  total: ");
  DEBUG_PRINTLN(total);
}

void MqttClient::publish(std::string topic, std::string payload)
{
  mqttClient.publish(topic.c_str(), AT_LEAST_ONCE, false, payload.c_str(), payload.size());
}