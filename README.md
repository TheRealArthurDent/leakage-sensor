# esp8266-wifi-participant
[![Check Arduino status](https://github.com/TheRealArthurDent/esp8266-wifi-participant/actions/workflows/check-arduino.yml/badge.svg)](https://github.com/TheRealArthurDent/esp8266-wifi-participant/actions/workflows/check-arduino.yml)
[![Compile Sketch status](https://github.com/TheRealArthurDent/esp8266-wifi-participant/actions/workflows/compile-sketch.yml/badge.svg)](https://github.com/TheRealArthurDent/esp8266-wifi-participant/actions/workflows/compile-sketch.yml)
[![Spell Check status](https://github.com/TheRealArthurDent/esp8266-wifi-participant/actions/workflows/spell-check.yml/badge.svg)](https://github.com/TheRealArthurDent/esp8266-wifi-participant/actions/workflows/spell-check.yml)

### Description

A tiny sample project that makes your ESP8266 a participant in a WiFi network.
On startup your board will try to connect to the specified WiFi network and will blink the built in ESP LED (GPIO 2) at 2 revolution per second while doing so.
Once successfully connected the node LED (GPIO 16) will blink at 1 revolution per 5 seconds.
If started with "#define DEBUG" it will log the progress via the Serial port.

### How-to-use

To be able to compile the project locally, copy the wifi_secrets.h.example to wifi_secrets.h and adjust the values within said file.
