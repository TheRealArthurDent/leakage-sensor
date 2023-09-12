#pragma once

#include "arduino-callable.hpp"
#include "metronome.hpp"
#include "master-caution.hpp"
#include "mqtt-client.hpp"
#include "water-sensor.hpp"
#include "alert.hpp"

const int LOOP_DURATION = 10000;
const int BLINK_INTERVAL = LOOP_DURATION / 2;

const int THRESHOLD_WATERLEVEL = 50;
const int THRESHOLD_LEAKAGE = 20;

const int BUZZER = D5;

const int RGB_LED_GREEN = D7;
const int RGB_LED_RED = D8;

/**
 * \brief The main application.
 */
class App : public ArduinoCallable
{
    Metronome metronome;
    MasterCaution masterCaution;
    MqttClient mqttClient;

    WaterSensor waterLevelSensor; //(A0, D1);
    WaterSensor leakageSensor;    //(A0, D2);

    Alert waterLevelAlert;
    Alert leakageAlert;

public:
    /// @brief The default constructor.
    App();
    ~App() override = default;

    /// @brief Arduino's <a href="https://www.arduino.cc/reference/en/language/structure/sketch/setup/">setup</a> function.
    auto setup() -> void override;
    /// @brief Arduino's <a href="https://www.arduino.cc/reference/en/language/structure/sketch/loop/">loop</a> function.
    auto loop() -> void override;
};
