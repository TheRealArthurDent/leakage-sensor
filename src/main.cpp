#include <Arduino.h>

#include "arduino-callable.hpp"
#include "app.hpp"

const int BUTTON = D6;

App *delegate; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

void IRAM_ATTR isr_buttonPressed()
{
  if (delegate != NULL)
  {
    delegate->acknowledge();
  }
}

// cppcheck-suppress unusedFunction
void setup()
{
  attachInterrupt(digitalPinToInterrupt(BUTTON), isr_buttonPressed, FALLING);

  delegate = new App();
  delegate->setup();
}

// cppcheck-suppress unusedFunction
void loop()
{
  delegate->loop();
}
