#pragma once

/**
 * \brief Gets values from an Iduino SE045 water sensor.
 *
 * This class is meant to operate an Iduino SE045 water sensor and perform
 * measurements via this sensor. It is designed to also control the power
 * supply of the sensor via a GPIO port, but can also operate an always-on
 * sensor.
 * Since the sensor is desgined to be operated with 5V but the NodeMCU does
 * only deliver 3,3V, the read values will never reach 1024 (100%).
 * However that doesn't really matter, since you have to somewhat calibrate
 * it anyway.
 * The sensor needs some time from being powered-up until it delivers
 * meaningful values which is why I ran some tests to
 * \li find a suitable up-time at which the measurements are reliable and
 * \li calibrate the sensor (find the respective raw values measured at this
 * point given a certain exposure to moist)
 *
 * The results of this calibration are added to the repository
 * as a spread sheet at docs/Calibration.ods.
 * The following image shows the calibration resuls.
 * \image html water-sensor-calibration.png
 * Following this result, the power-up time before a measurement is defined at
 * 100 ms. This also means that a WaterSensor configured to be powered up on
 * demand, consumes 100 ms per measurement.
 * To circumvent this, the sensor can be operated always-on.
 * \see WaterSensor(int, int).
 */
class WaterSensor
{
public:
    /**
     * \brief Constructor.
     *
     * \param sensorPin
     * \parblock
     * The GPIO pin that the sensor is connected to. Of cousrse this should be an
     * analog GPIO pin.
     * \param powerPin
     * \parblock
     * [OPTIONAL] The GPIO pin that controls the power of the sensor.
     * It is highly recommended to control the power supply of your sensor, as it
     * will wear quicker when constantly powered. In case you don't have a free
     * GPIO port available, you can still go with constant power and omit this
     * value.
     * If a powerPin is specified, the controller will power the sensor on demand
     * (when ever getLevel is called).
     */
    WaterSensor(int sensorPin, int powerPin = -1);
    WaterSensor(WaterSensor const &);            // Don't implement.
    WaterSensor &operator=(WaterSensor const &); // Don't implement.

    /**
     * \brief Measures and returns the current water level.
     *
     * In case a powerPin has been specified, the method will return a value
     * after ~100 ms, as this is the time the sensor will be powered up,
     * before performing the analog read.
     * If the sample rate you are looking for requires a lower value, you
     * might wanna NOT specify a powerPin and power your sensor constantly.
     * In the latter case, the method will return a value (almost) immediately.
     *
     * \return The current water level.
     */
    auto getLevel() -> int;

private:
    int sensorPin;
    int powerPin;

    auto isPoweredOnDemand() -> bool;
};