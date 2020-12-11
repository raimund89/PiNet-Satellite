#ifndef LC_WIFI
#define LC_WIFI

#include <WiFiManager.h>

WiFiManager wifiManager;

void configModeCallback(WiFiManager *manager);

void InitWifi()
{
  wifiManager.setHostname("Skynet_RGB01");
  // So we can do something when config mode is entered
  wifiManager.setAPCallback(configModeCallback);
  
  // Put some safeties around this (if(!autoconnect), do something)
  wifiManager.autoConnect("SkynetLED");
}

void configModeCallback(WiFiManager *manager) {
  // Wifi is configured.
}

#endif
