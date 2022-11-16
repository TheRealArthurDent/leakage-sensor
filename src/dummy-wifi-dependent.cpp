#include "dummy-wifi-dependent.h"
#include "debug.h"

// cppcheck-suppress unusedFunction
void DummyWifiDependent::onWifiConnectionEstablished()
{
  DEBUG_PRINTLN("DummyWifiDependent connected!");
}

// cppcheck-suppress unusedFunction
void DummyWifiDependent::onWifiConnectionLost()
{
  DEBUG_PRINTLN("DummyWifiDependent disconnected!");
}