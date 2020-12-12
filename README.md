# PiNet-Satellite
This repository contains the firmware to make any ESP8266 (or ESP8285) based device part of the PiNet local network. The firmware is only meant for devices that need active control, such as switches and lights. For sensors there will be another project in the future.

# Installation
You can upload it to the ESP8266 chip using the Arduino IDE. There are lots of tutorials on the web to find out how to connect the chip to your computer. After the first upload, you can also use Arduino OTA to flash a new version to the ESP8266.

# Status
The current software is really just an early setup to make the device work. A lot of basic code is still missing.

# Features
- [x] WiFiManager to facilitate easy connecting to a network
- [x] SSDP multicast response for device discovery
- [x] Webserver for interaction
- [x] ArduinoOTA to allow flashing over wifi
- [ ] Configuration as different device types: switch, light, rgb (3x led), programmable led-strip, etc.
- [ ] Pin naming
- [ ] Pin modes (analog, digital)
