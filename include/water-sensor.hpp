#pragma once

/**
 * \brief
 */
class WaterSensor
{
public:
    WaterSensor(int sensorPin, int powerPin = -1);
    WaterSensor(WaterSensor const &);            // Don't implement.
    WaterSensor &operator=(WaterSensor const &); // Don't implement.

    /**
     * \brief Measures and returns the current water level.
     * \return The current water level.
     */
    auto getLevel() -> int;

private:
    int sensorPin;
    int powerPin;

    auto isPoweredOnDemand() -> bool;
};