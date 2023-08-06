#pragma once

#include "arduino-callable.hpp"
#include "metronome.hpp"

const int LOOP_DURATION = 5000;
const int BLINK_INTERVAL = LOOP_DURATION / 2;

/**
 * \brief The main application.
 */
class App : public ArduinoCallable
{
    Metronome metronome;

public:
    /// @brief The default constructor.
    App();
    ~App(){};

    /// @brief Arduino's <a href="https://www.arduino.cc/reference/en/language/structure/sketch/setup/">setup</a> function.
    auto setup() -> void;
    /// @brief Arduino's <a href="https://www.arduino.cc/reference/en/language/structure/sketch/loop/">loop</a> function.
    auto loop() -> void;

private:
    // hide copy constructor and = operator
    App(App const &);                // Don't implement.
    App(App &&) noexcept;            // Don't implement.
    void operator=(App const &);     // Don't implement.
    void operator=(App &&) noexcept; // Don't implement.

    auto blinkLed() -> void;
};
