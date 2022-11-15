#include "debug.h"

void initDebugging() {
#ifdef DEBUG
  Serial.begin(115200);
#endif
  DEBUG_PRINTLN("Debugging initialized.");
  DEBUG_PRINTLN();
}