#include "dummy-wifi-dependent.h"
#include "debug.h"

void DummyWifiDependent::onWifiConnectionEstablished() {
  DEBUG_PRINTLN("DummyWifiDependent connected!");
}

void DummyWifiDependent::onWifiConnectionLost() {
  DEBUG_PRINTLN("DummyWifiDependent disconnected!");
}