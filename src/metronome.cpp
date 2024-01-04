#include <Arduino.h>
#include "metronome.hpp"

void Metronome::waitForNextCycle()
{
  delay(cycleDuration - (millis() % cycleDuration));
}
