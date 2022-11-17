# esp8266-wifi-participant
[![PlatformIO Code Check](https://github.com/TheRealArthurDent/esp8266-wifi-participant/actions/workflows/platformio-check.yaml/badge.svg)](https://github.com/TheRealArthurDent/esp8266-wifi-participant/actions/workflows/platformio-check.yaml)
[![PlatformIO CI](https://github.com/TheRealArthurDent/esp8266-wifi-participant/actions/workflows/platformio-ci.yaml/badge.svg)](https://github.com/TheRealArthurDent/esp8266-wifi-participant/actions/workflows/platformio-ci.yaml)
[![CPP Lint status](https://github.com/TheRealArthurDent/esp8266-wifi-participant/actions/workflows/cpp-lint.yaml/badge.svg)](https://github.com/TheRealArthurDent/esp8266-wifi-participant/actions/workflows/cpp-lint.yaml)
[![Spell Check status](https://github.com/TheRealArthurDent/esp8266-wifi-participant/actions/workflows/spell-check.yaml/badge.svg)](https://github.com/TheRealArthurDent/esp8266-wifi-participant/actions/workflows/spell-check.yaml)

###Compatibility with Arduino IDE

[![Check Arduino status](https://github.com/TheRealArthurDent/esp8266-wifi-participant/actions/workflows/check-arduino.yaml/badge.svg)](https://github.com/TheRealArthurDent/esp8266-wifi-participant/actions/workflows/check-arduino.yaml)
[![Compile Sketch status](https://github.com/TheRealArthurDent/esp8266-wifi-participant/actions/workflows/compile-sketch.yaml/badge.svg)](https://github.com/TheRealArthurDent/esp8266-wifi-participant/actions/workflows/compile-sketch.yaml)


### Description

A tiny sample project that makes your ESP8266 a participant in a WiFi network.
On startup your board will try to connect to the specified WiFi network and will blink the built in ESP LED (GPIO 2) at 2 revolution per second while doing so.
Once successfully connected the node LED (GPIO 16) will blink at 1 revolution per 5 seconds.
If started with "#define DEBUG" it will log the progress via the Serial port.

### How-to-use

To be able to compile the project locally, copy the wifi_secrets.h.example to wifi_secrets.h and adjust the values within said file.
