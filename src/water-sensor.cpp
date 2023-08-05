#include "water-sensor.hpp"
#include <Arduino.h>

WaterSensor::WaterSensor(int sensorPin, int powerPin)
{
    this->sensorPin = sensorPin;
    pinMode(sensorPin, INPUT);
    this->powerPin = powerPin;
    if (isPoweredOnDemand())
    {
        pinMode(powerPin, OUTPUT);
    }
}

int WaterSensor::getLevel()
{
    if (isPoweredOnDemand())
    {
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(powerPin, HIGH);
        delay(10);
    }
    int level = analogRead(sensorPin);
    if (isPoweredOnDemand())
    {
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(powerPin, LOW);
    }
    return level;
}

bool WaterSensor::isPoweredOnDemand()
{
    return powerPin != -1;
}