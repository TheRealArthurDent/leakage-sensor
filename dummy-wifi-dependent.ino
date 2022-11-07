#include "dummy-wifi-dependent.h"
#include "debug.h"

void DummyWifiDependent::onConnectionEstablished() {
  DEBUG_PRINTLN("DummyWifiDependent connected!");
}

void DummyWifiDependent::onConnectionLost() {
  DEBUG_PRINTLN("DummyWifiDependent disconnected!");
}