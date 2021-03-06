#ifndef LC_SETTINGS
#define LC_SETTINGS

#include <LittleFS.h>
#include <ArduinoJson.h>

#define SETTINGS_FILE "/settings.json"
#define SETTINGS_RAM 1300

#define DEFAULT_FRIENDLY_NAME "Bedchamber Fancy Light"
#define DEFAULT_AP_NAME "PiNet Satellite AP"
#define DEFAULT_DEVICE_TYPE 0
#define DEFAULT_HTTP_PORT 80
#define DEFAULT_TIME_OFFSET 0

#define MANUFACTURER "Espressif"
#define DEVICE_TYPE "RGBW"

/*
 * Example settings file
 * 
 * {
 *   "general": {
 *     "friendly_name": "Christmas Lamp",
 *     "ap_name": "PiNet Satellite AP",
 *     "http_port", 80
 *   },
 *   "pins": {
 *     "0": {
 *       "enabled": true,
 *       "type": 1,
 *       "name": "green"
 *     }
 *   }
 * }
 * 
 */

enum PinType {
  INPUT_DIGITAL,  // Boolean value
  INPUT_ANALOG,   // Integer (short) value NOTE: NOT POSSIBLE WITH ESP8266
  OUTPUT_DIGITAL, // Boolean value
  OUTPUT_ANALOG,  // Integer (short) value
  BATTERY_VOLTAGE // Floating point value
};

struct Pin {
  bool configured;
  bool enabled;
  PinType type;
  char name[10];
};

struct Config {
  char friendly_name[64];
  char ap_name[64];
  int http_port;

  long time_offset;

  Pin pins[17];
};

String last_time_update;

Config conf;

String getSettings() {
  String ret;
  File file = LittleFS.open(SETTINGS_FILE, "r");
  
  if(!file) {
    String ret = "File not found";
  }

  while(file.available()) {
    ret += (char)file.read();
  }
  
  file.close();
  return ret;
}

bool saveSettings() {
  LittleFS.remove(SETTINGS_FILE);

  File file = LittleFS.open(SETTINGS_FILE, "w");
  if(!file) {
    return false;
  }

  DynamicJsonDocument doc(SETTINGS_RAM);

  // Parse settings
  doc["general"]["friendly_name"] = conf.friendly_name;
  doc["general"]["ap_name"] = conf.ap_name;
  doc["general"]["http_port"] = conf.http_port;
  doc["general"]["time_offset"] = conf.time_offset;

  for(unsigned int i=0; i<sizeof(conf.pins)/sizeof(Pin); i++) {
    if(conf.pins[i].configured){
      char num[5];
      itoa(i, num, 10);
      
      doc["pins"][num]["enabled"] = conf.pins[i].enabled;
      doc["pins"][num]["type"] = conf.pins[i].type;
      doc["pins"][num]["name"] = conf.pins[i].name;
    }
  }

  if(serializeJson(doc, file) == 0) {
    // An error occured
    return false;
  }

  // Close the file
  file.close();

  return true;
}

bool defaultSettings() {
  // The settings file doesn't exist, so assume this is the first time
  // this device is booting to PiNet. Format the LittleFS and save the 
  // default settings to file.
  LittleFS.format();

  // Set default setting values
  strlcpy(conf.friendly_name, DEFAULT_FRIENDLY_NAME, sizeof(DEFAULT_FRIENDLY_NAME));
  strlcpy(conf.ap_name, DEFAULT_AP_NAME, sizeof(DEFAULT_AP_NAME));
  conf.http_port = DEFAULT_HTTP_PORT;
  conf.time_offset = DEFAULT_TIME_OFFSET;

  for(unsigned int i=0; i<sizeof(conf.pins)/sizeof(Pin); i++) {
    conf.pins[i].configured = false;
  }

  // Now save these as the first template
  return saveSettings();
}

bool loadSettings() {
  if(LittleFS.exists(SETTINGS_FILE)) {
    File file = LittleFS.open(SETTINGS_FILE, "r");
    if(!file) {
      // An error occured.. Not sure what to do with that..
      return false;
    }
    
    DynamicJsonDocument doc(SETTINGS_RAM);
    DeserializationError error = deserializeJson(doc, file);
    if(error) {
      // An error occured
      return false;
    }

    // Parse settings
    strlcpy(conf.friendly_name, doc["general"]["friendly_name"] | DEFAULT_FRIENDLY_NAME, sizeof(conf.friendly_name));
    strlcpy(conf.ap_name, doc["general"]["ap_name"] | DEFAULT_AP_NAME, sizeof(conf.ap_name));
    conf.http_port = doc["general"]["http_port"] | DEFAULT_HTTP_PORT;
    conf.time_offset = doc["general"]["time_offset"] | DEFAULT_TIME_OFFSET;

    for(JsonPair kv: doc["pins"].as<JsonObject>()) {
      int pin = atoi(kv.key().c_str());

      conf.pins[pin].configured = true;
      JsonObject p = kv.value().as<JsonObject>();
      conf.pins[pin].enabled = p["enabled"];
      conf.pins[pin].type = p["type"];
      strlcpy(conf.pins[pin].name, p["name"] | "undefined", sizeof(p["name"]));
    }

    // Close the file.
    file.close();
    
    return true;
  }
  else {
    return defaultSettings();
  }
}

void InitSettings() {
  LittleFS.begin();

  loadSettings();
}

#endif
