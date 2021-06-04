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
  InitWebsocket();
  InitSSDP();
}


// The total delay is 20ms, which means we can only do a max of 50 operations per second
void loop() {
  HandleOTA();
  delay(5);

  if(!handling_ota){
    HandleNTP();
    delay(5);
    HandleWebserver();
    delay(5);
    HandleWebsocket();
    delay(5);
  }
}
