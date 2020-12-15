#include "lc_gpio.h"
#include "lc_settings.h"
#include "lc_wifi.h"
#include "lc_ota.h"
#include "lc_webserver.h"

void setup() {
  InitSettings();
  InitGPIO();
  Program_CycleColors(0.2);
  delay(2000);
  Program_CycleColors(0.1);
  InitWifi();
  InitNTP();
  InitOTA();
  delay(1000);
  InitWebserver();
  InitSSDP();
}

void loop() {
  HandleNTP();
  HandleOTA();
  HandleWebserver();
}
