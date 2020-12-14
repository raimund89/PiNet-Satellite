#ifndef LC_SETTINGS
#define LC_SETTINGS

#include <FS.h>
#include <ArduinoJson.h>

#define SETTINGS_FILE "/settings.json"
#define SETTINGS_RAM 1024

/*******************************************/
/* Device types:                           */
/* 0 - Basic switch                        */
/* 1 - Basic light (pwm brightness)        */
/*******************************************/

#define DEFAULT_FRIENDLY_NAME "Christmas Fractal Lamp"
#define DEFAULT_AP_NAME "PiNet Satellite AP"
#define DEFAULT_DEVICE_TYPE 0
#define DEFAULT_PORT 80

struct Config {
  char friendly_name[64];
  char ap_name[64];
  int device_type;
  int port;
};

Config conf;

bool saveSettings() {
  SPIFFS.remove(SETTINGS_FILE);

  File file = SPIFFS.open(SETTINGS_FILE, "w");
  if(!file) {
    return false;
  }

  StaticJsonDocument<SETTINGS_RAM> doc;

  // Parse settings

  if(serializeJson(doc, file) == 0) {
    // An error occured
    return false;
  }

  // Close the file
  file.close();
}

bool loadSettings() {
  if(SPIFFS.exists(SETTINGS_FILE)) {
    File file = SPIFFS.open(SETTINGS_FILE, "r");
    if(!file) {
      // An error occured.. Not sure what to do with that..
      return false;
    }
    
    StaticJsonDocument<SETTINGS_RAM> doc;
    DeserializationError error = deserializeJson(doc, file);
    if(error) {
      // An error occured
      return false;
    }

    // Parse settings
    strlcpy(conf.friendly_name, doc["friendly_name"] | DEFAULT_FRIENDLY_NAME, sizeof(conf.friendly_name));
    strlcpy(conf.ap_name, doc["ap_name"] | DEFAULT_AP_NAME, sizeof(conf.ap_name));
    conf.device_type = doc["device_type"] | DEFAULT_DEVICE_TYPE;
    conf.port = doc["port"] | DEFAULT_PORT;

    // Close the file.
    file.close();
  }
  else {
    // The settings file doesn't exist, so assume this is the first time
    // this device is booting to PiNet. Format the SPIFFS and save the 
    // default settings to file.
    SPIFFS.format();

    // Set default setting values
    strlcpy(conf.friendly_name, DEFAULT_FRIENDLY_NAME, sizeof(DEFAULT_FRIENDLY_NAME));
    strlcpy(conf.ap_name, DEFAULT_AP_NAME, sizeof(DEFAULT_AP_NAME));
    conf.device_type = DEFAULT_DEVICE_TYPE;
    conf.port = DEFAULT_PORT;

    // Now save these as the first template
    return saveSettings();
  }
}

void InitSettings() {
  SPIFFS.begin();

  loadSettings();
}

#endif
