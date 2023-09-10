#pragma once

#include "arduino-callable.hpp"
#include "metronome.hpp"
#include "master-caution.hpp"
#include "mqtt-client.hpp"

const int LOOP_DURATION = 2000;
const int BLINK_INTERVAL = LOOP_DURATION / 2;

/**
 * \brief The main application.
 */
class App : public ArduinoCallable
{
    Metronome metronome;
    MasterCaution masterCaution;
    MqttClient mqttClient;

public:
    /// @brief The default constructor.
    App();
    ~App() override = default;

    /// @brief Arduino's <a href="https://www.arduino.cc/reference/en/language/structure/sketch/setup/">setup</a> function.
    auto setup() -> void override;
    /// @brief Arduino's <a href="https://www.arduino.cc/reference/en/language/structure/sketch/loop/">loop</a> function.
    auto loop() -> void override;

private:
    auto blinkLed() -> void;
};
