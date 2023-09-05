#include "metronome.hpp"
#include <Arduino.h>

void Metronome::waitForNextCycle()
{
    delay(cycleDuration - (millis() % cycleDuration));
}