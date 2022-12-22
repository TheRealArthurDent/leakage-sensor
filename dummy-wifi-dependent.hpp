#pragma once

#include "wifi-dependent.hpp"

class DummyWifiDependent : public WifiDependent
{

public:
  virtual void onWifiConnectionEstablished();
  virtual void onWifiConnectionLost();
};
