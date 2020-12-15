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
- [ ] NTP sync with timezone detection (best guess ip-api)
- [ ] Configuration as different device presets: switch, light, rgb (3x led), programmable led-strip, Sonoff S20/S26, etc.
- [ ] Pin naming
- [ ] Pin modes (analog, digital)
- [ ] Automatic pin response (react to state change in other pins)
- [ ] Multicast new status so everyone is updated

# Known issues
- Device still shows up as softAP named AI-THINKER_XXXXXX (last 6 digits of MAC-address)
- No secure connection (ssl, password)
- No state persistence after power cycle or restart
- Lots of static names
- No ability to reset WiFi settings

# How it works
The firmware makes use of WiFiManager to connect and store wifi information. The first time you start up the device after flashing, it will present itself as a wifi hotspot. Connect with a laptop or phone and it will automatically show you a web page where you can connect the device to your home wifi (you'll need the wifi password for that).

When wifi is configured correctly, the device will go through a number of steps. It loads the settings from the SPIFFS (friendly name, pin configuration, etc.) and configures the GPIO accordingly. Then it will connect to the wifi network and initialize the OTA functionality. The current time is synchronized with an NTP server (for timer functionality) and the webserver is started. Also, an SSDP discovery protocol is started so the device can be found by PiNet Ground Control and PiNet Major Tom.

Every available pin of the ESP8266 can be configured. Which pins are actually available is not checked by the firmware! So you will have to check this yourself. You can configure every pin either as a digital or analog output with a corresponding value, or as a digital input. Also, you can set whether it is currently enabled or not (to temporarily enable or disable pins for example without losing the configuration). The pin value can be set directly using either the web interface or the API (used by Ground Control and Major Tom), or it can follow the output of another pin. The last function is useful when a status LED needs to be changed according to another pin, such as for the Sonoff S20/S26, or when the device has a physical switch to turn a pin on/off. 

# Acknowledgements
Many people should be thanked, including the entire ESP8266 and Arduino community. This list is just the list of authors of the APIs and libraries used in this project:
- tzapu for the (https://github.com/tzapu/WiFiManager)[WiFiManager] library
- bblanchon for the (https://github.com/bblanchon/ArduinoJson)[ArduinoJson] library
- nayarsystems for the (https://github.com/nayarsystems/posix_tz_db)[timezone data file]
- ip-api.com for their open API to receive timezone information
