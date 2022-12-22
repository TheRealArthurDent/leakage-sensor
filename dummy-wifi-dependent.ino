#include "dummy-wifi-dependent.hpp"
#include "debug.h"

void DummyWifiDependent::onWifiConnectionEstablished() {
  DEBUG_PRINTLN("DummyWifiDependent connected!");
}

void DummyWifiDependent::onWifiConnectionLost() {
  DEBUG_PRINTLN("DummyWifiDependent disconnected!");
}