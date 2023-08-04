#include "metronom.hpp"
#include <Arduino.h>

void Metronom::waitForNextCycle()
{
    delay(cycleDuration - (millis() % cycleDuration));
}