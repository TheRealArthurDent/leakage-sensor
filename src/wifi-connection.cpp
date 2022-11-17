#include "wifi-connection.h"
#include <Ticker.h>
#include "wifi-secrets.h"
#include "led.h"

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
Ticker wifiReconnectTimer;

char wifiSsid[] = SECRET_WIFI_SSID;
char wifiPass[] = SECRET_WIFI_PASS;
char hostname[] = SECRET_HOSTNAME;

void WifiConnection::init()
{
  DEBUG_PRINT("Connecting to ");
  DEBUG_PRINTLN(wifiSsid);

  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostname);
  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);
  connect();
}

void WifiConnection::init(std::list<WifiDependent *> dependentsList)
{
  dependents.clear();
  std::for_each(dependentsList.begin(), dependentsList.end(), [this](WifiDependent *d)
                { dependents.push_back(d); });

  init();
}

// cppcheck-suppress unusedFunction
bool WifiConnection::isConnected()
{
  return connected;
}

void WifiConnection::setConnected(bool conn)
{
  connected = conn;
}

void WifiConnection::notifyDependentsConnected()
{
  std::for_each(dependents.begin(), dependents.end(), [](WifiDependent *d)
                { d->onWifiConnectionEstablished(); });
}

void WifiConnection::notifyDependentsDisconnected()
{
  std::for_each(dependents.begin(), dependents.end(), [](WifiDependent *d)
                { d->onWifiConnectionLost(); });
}

void WifiConnection::connect()
{

  WiFi.begin(wifiSsid, wifiPass);

  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(led_built_in_ESP, LOW);
    delay(250);
    digitalWrite(led_built_in_ESP, HIGH);
    delay(250);
    DEBUG_PRINT(".");
  }
}

void WifiConnection::onWifiConnect(const WiFiEventStationModeGotIP &event)
{
  DEBUG_PRINT("Connected to WiFi ");
  DEBUG_PRINTLN(wifiSsid);
  DEBUG_PRINT("IP address: ");
  DEBUG_PRINTLN(WiFi.localIP());

  getInstance().setConnected(true);
  getInstance().notifyDependentsConnected();
}

void WifiConnection::onWifiDisconnect(const WiFiEventStationModeDisconnected &event)
{
  DEBUG_PRINTLN("Disconnected from WiFi ");
  DEBUG_PRINTLN(wifiSsid);

  getInstance().setConnected(false);
  getInstance().notifyDependentsDisconnected();

  // Apparently this is not even required, since ESP8266WiFiClass tries to reconnect like a mad man anyway.
  // wifiReconnectTimer.once(2, connectToWifi);
}