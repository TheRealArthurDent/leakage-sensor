# esp8266-ota-capable

License

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Status

[![PlatformIO Code Check](https://github.com/TheRealArthurDent/esp8266-ota-capable/actions/workflows/platformio-check.yaml/badge.svg)](https://github.com/TheRealArthurDent/esp8266-ota-capable/actions/workflows/platformio-check.yaml)
[![PlatformIO CI](https://github.com/TheRealArthurDent/esp8266-ota-capable/actions/workflows/platformio-ci.yaml/badge.svg)](https://github.com/TheRealArthurDent/esp8266-ota-capable/actions/workflows/platformio-ci.yaml)
[![CPP Lint status](https://github.com/TheRealArthurDent/esp8266-ota-capable/actions/workflows/cpp-lint.yaml/badge.svg)](https://github.com/TheRealArthurDent/esp8266-ota-capable/actions/workflows/cpp-lint.yaml)
[![Spell Check status](https://github.com/TheRealArthurDent/esp8266-ota-capable/actions/workflows/spell-check.yaml/badge.svg)](https://github.com/TheRealArthurDent/esp8266-ota-capable/actions/workflows/spell-check.yaml)
[![Markdown Lint](https://github.com/TheRealArthurDent/esp8266-ota-capable/actions/workflows/markdown-lint.yaml/badge.svg)](https://github.com/TheRealArthurDent/esp8266-ota-capable/actions/workflows/markdown-lint.yaml)

## Compatibility with Arduino IDE

[![Check Arduino status](https://github.com/TheRealArthurDent/esp8266-ota-capable/actions/workflows/check-arduino.yaml/badge.svg)](https://github.com/TheRealArthurDent/esp8266-ota-capable/actions/workflows/check-arduino.yaml)
[![Compile Sketch status](https://github.com/TheRealArthurDent/esp8266-ota-capable/actions/workflows/compile-sketch.yaml/badge.svg)](https://github.com/TheRealArthurDent/esp8266-ota-capable/actions/workflows/compile-sketch.yaml)

Always fresh

[![Renovate enabled](https://img.shields.io/badge/renovate-enabled-brightgreen.svg)](https://renovatebot.com/)

Open topics

[![GitHub issues](https://img.shields.io/github/issues/TheRealArthurDent/esp8266-ota-capable.svg)](https://GitHub.com/TheRealArthurDent/esp8266-ota-capable/issues/)
[![GitHub pull-requests](https://img.shields.io/github/issues-pr/TheRealArthurDent/esp8266-ota-capable.svg)](https://GitHub.com/TheRealArthurDent/esp8266-ota-capable/pull/)

## Description

A tiny sample project that is based on esp8266-wifi-participant
but is updatable over-the-air.
On startup your board will try to connect to the specified WiFi network and will
blink the built in ESP LED (GPIO 2) at 2 revolution per second while doing so.
Once successfully connected the node LED (GPIO 16) will blink at 1 revolution
per 5 seconds.
If started with "#define DEBUG" it will log the progress via the Serial port.

## How-to-use

To be able to compile the project locally, copy the secrets.ini.example
to secrets.ini and adjust the values within said file.
