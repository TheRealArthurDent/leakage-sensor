#ifndef WIFI_DEPENDENT_H
#define WIFI_DEPENDENT_H

class WifiDependent {

public:
  virtual void onConnectionEstablished() = 0;
  virtual void onConnectionLost() {}
};

#endif