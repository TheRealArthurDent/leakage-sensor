#pragma once

#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <list>
#include <vector>
#include "wifi-dependent.hpp"

/**
 * \brief A controller for a WiFi connection.
 *
 * A singleton that will take care of your WiFi connection. It will try to
 * establish a connection, attempt reconnects in case of a connection loss
 * and inform registered \c WifiDependent s about successful connects as well
 * as connection losses by calling their \c onWifiConnectionEstablished or
 * \c onWifiConnectionLost callback respectively.
 */
class WifiConnection
{
  WiFiEventHandler wifiConnectHandler;
  WiFiEventHandler wifiDisconnectHandler;
  // Ticker wifiReconnectTimer;

  bool connected = false;
  std::vector<WifiDependent *> dependents;

  // Singleton "constructor"
public:
  /**
   * Gets the \c Singleton instance.
   */
  static auto getInstance() -> WifiConnection &
  {
    static WifiConnection instance;
    return instance;
  }
  // hide constructor, copy constructor and = operator
private:
  WifiConnection() = default;                 // hide default constructor
  WifiConnection(WifiConnection const &);     // Don't implement.
  WifiConnection(WifiConnection &&) noexcept; // Don't implement.
  void operator=(WifiConnection const &);     // Don't implement.
  void operator=(WifiConnection &&) noexcept; // Don't implement.
  ~WifiConnection() = default;                // Don't implement.

  // normal methods
public:
  /**
   * Returns the WiFi connection status.
   *
   * \return \c true in case the WiFi connection is established
   * or \c false otherwise.
   */
  auto isConnected() -> bool;

  /**
   * Initializes the controller while registering a collection of
   * \c WifiDependent s.
   *
   * \param dependents A collection of instances that depend on a WiFi
   * connection. The dependents will be informed about changes in the
   * connection's status.
   */
  void init(std::list<WifiDependent *> dependents);
  // void addDependent
  // void removeDependent

private:
  /**
   * An init method, that does not register any dependents.
   * It's currently private since no add or remove methods for
   * \c WifiDependents exist. Might become \c public in case that changes.
   */
  void init();
  void connect();
  void setConnected(bool connected);
  void notifyDependentsConnected();
  void notifyDependentsDisconnected();

  static void onWifiConnect(const WiFiEventStationModeGotIP &event);
  static void onWifiDisconnect(const WiFiEventStationModeDisconnected &event);
};
