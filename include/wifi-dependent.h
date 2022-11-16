#ifndef WIFI_DEPENDENT_H
#define WIFI_DEPENDENT_H

const class WifiDependent
{

public:
  virtual void onWifiConnectionEstablished() = 0;
  virtual void onWifiConnectionLost() {}
};

#endif