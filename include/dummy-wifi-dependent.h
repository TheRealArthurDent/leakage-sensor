#ifndef DUMMY_WIFI_DEPENDENT_H
#define DUMMY_WIFI_DEPENDENT_H

#include "wifi-dependent.h"

class DummyWifiDependent : public WifiDependent {

public:
  virtual void onWifiConnectionEstablished();
  virtual void onWifiConnectionLost();
};

#endif