#ifndef LC_WIFI
#define LC_WIFI

#include <WiFiManager.h>
#include <ESP8266SSDP.h>
#include <ESP8266HTTPClient.h>
#include <coredecls.h>
#include <time.h>
#include "lc_settings.h"

WiFiManager wifiManager;

#define SSDP_URL String("/")
#define SSDP_SCHEMA_URL "description.xml"
#define SSDP_SERIAL_NUMBER ESP.getChipId()
#define SSDP_MODEL_NAME "RGB"
#define SSDP_MODEL_NUMBER "01"
#define SSDP_MANUFACTURER "PiNet"

void InitWifi()
{
  wifiManager.setHostname("PiNet_RGB01");
  
  // Put some safeties around this (if(!autoconnect), do something)
  wifiManager.autoConnect(conf.ap_name);
}

void InitSSDP() {
  SSDP.setSchemaURL(SSDP_URL + SSDP_SCHEMA_URL);
  SSDP.setHTTPPort(conf.http_port);
  SSDP.setName(conf.friendly_name);
  SSDP.setSerialNumber(SSDP_SERIAL_NUMBER);
  SSDP.setURL(SSDP_URL);
  SSDP.setModelName(SSDP_MODEL_NAME);
  SSDP.setModelNumber(SSDP_MODEL_NUMBER);
  SSDP.setManufacturer(SSDP_MANUFACTURER);
  SSDP.begin();
}

String getTimeString() {
  time_t now = time(nullptr);
  tm* local = localtime(&now);
  return String(local->tm_hour) + ":" + String(local->tm_min) + ":" + String(local->tm_sec);
}

void time_is_set() {
  last_time_update = getTimeString();
}

void InitNTP() {
  // Set callback for whenever the time is changed
  settimeofday_cb(time_is_set);
  
  // We're starting up, so check the time offset.
  HTTPClient http;
  http.useHTTP10(true);
  http.begin("http://ip-api.com/json/?fields=33571266");
  http.GET();

  DynamicJsonDocument doc(2048);
  deserializeJson(doc, http.getStream());
  
  conf.time_offset = doc["offset"] | DEFAULT_TIME_OFFSET;
  configTime(conf.time_offset, 0, "pool.ntp.org");

  http.end();
  saveSettings();
}

void HandleNTP() {
  // TODO: If current time is 2:05am, update the clock
  // Or maybe even more frequently
  /*if(millis() - lastNTPUpdate > 300000) {
    timeClient.update();
    lastNTPUpdate = millis();
  }*/
}

#endif
