#pragma once

class WifiDependent
{

public:
  virtual void onConnectionEstablished() = 0;
  virtual void onConnectionLost() {}
};