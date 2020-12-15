#ifndef LC_WEBSERVER
#define LC_WEBSERVER

#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

#include "lc_gpio.h"
#include "lc_templates.h"
#include "lc_settings.h"

ESP8266WebServer server(80);

void InitWebserver()
{
  server.on("/", []() {
    String str = FrontMatter() + HeadMatter();
    str += ButtonMatter("/info", "Information");
    str += ButtonMatter("/config", "Configuration");
    str += ButtonMatter("/upgrade", "Upgrade");
    str += BackMatter();
    
    server.send(200, "text/html", str);
  });
  server.on("/info", []() {
    String str = FrontMatter() + HeadMatter();
    
    str += InfoHeader("General");
    str += InfoRow("Manufacturer", "Espressif");
    str += InfoRow("Device Type", "RGB");
    str += InfoRow("Friendly Name", conf.friendly_name);
    str += InfoRow("PiNet version", "0.1");
  
    long mils = millis();
    int mins = int((mils/(1000*60)) % 60);
    int hrs = int((mils/(1000*60*60)) % 24);
    int dys = int((mils/(1000*60*60*24)) % 365);
    str += InfoRow("Uptime", String(dys) + "d " + hrs + "h " + mins + "m");
    str += InfoRow("Last reset reason", ESP.getResetReason());
    
    str += InfoHeader("Chip Info");
    str += InfoRow("Chip ID", "0x" + String(ESP.getChipId(), HEX));
    str += InfoRow("Flash Chip ID", "0x" + String(ESP.getFlashChipId(), HEX));
    str += InfoRow("Flash size", String(ESP.getFlashChipSize()/1024) + "kB");
    str += InfoRow("Program size", String(ESP.getSketchSize()/1024) + "kB");
    str += InfoRow("Free space", String(ESP.getFreeSketchSpace()/1024) + "kB");
    str += InfoRow("Free memory", String(ESP.getFreeHeap()/1024) + "kB");
    //str += InfoRow("Flash writes", "");
    //str += InfoRow("Boot count", "");

    str += InfoHeader("WiFi Info");
    str += InfoRow("SSID", WiFi.SSID());
    str += InfoRow("Network IP", WiFi.localIP().toString());
    str += InfoRow("MAC-address", WiFi.macAddress());
    str += InfoRow("Gateway", WiFi.gatewayIP().toString());
    str += InfoRow("DNS Server", WiFi.dnsIP().toString());
    str += InfoRow("Subnet Mask", WiFi.subnetMask().toString());
    str += InfoRow("Current Time", String(timeClient.getHours()) + ":" + String(timeClient.getMinutes()) + ":" + String(timeClient.getSeconds()));
    
    str += InfoHeader("SSDP Discovery");
    str += InfoRow("Schema URL", SSDP_URL + SSDP_SCHEMA_URL);
    str += InfoRow("Port", String(conf.http_port));
    str += InfoRow("Name", conf.friendly_name);
    str += InfoRow("Serial Number", String(SSDP_SERIAL_NUMBER));
    str += InfoRow("Manufacturer", SSDP_MANUFACTURER);
    str += InfoRow("Model Name", SSDP_MODEL_NAME);
    str += InfoRow("Model Number", SSDP_MODEL_NUMBER);

    str += ButtonMatter("/", "Back");
    
    str += BackMatter();

    server.send(200, "text/html", str);
  });
  server.on("/config", []() {
    String str = FrontMatter() + HeadMatter();

    if(server.hasArg("o")) {
      String page = server.arg("o");

      if(page == "wifi"){
        str += "Wifi Settings";
      }
      else if(page == "ssdp") {
        str += "SSDP Settings";
      }
      else if(page == "dev") {
        str += "Device Settings";
      }
      else if(page == "timers") {
        str += "Timer Settings";
      }
      
      str += ButtonMatter("/config", "Back");
    }
    else {
      str += ButtonMatter("/config?o=wifi", "WiFi");
      str += ButtonMatter("/config?o=ssdp", "SSDP");
      str += ButtonMatter("/config?o=dev", "Device");
      str += ButtonMatter("/config?o=timers", "Timers");
      str += ButtonMatter("/config.json", "Config File");
      str += ButtonMatter("/", "Back");
    }

    str += BackMatter();

    server.send(200, "text/html", str);
  });
  server.on("/config.json", []() {
    server.send(200, "text/json", getSettings());
  });
  server.on("/restart", []() {
    server.sendHeader("Location", String("/"), true);
    server.send(302, "text/plain", "");
    ESP.restart();
  });
  server.on("/cm", []() {
    if(server.hasArg("cmnd")) {
      String cmnd = server.arg("cmnd");

      if(cmnd == "DeviceName") {
        DynamicJsonDocument doc(50);
        doc["DeviceName"] = "RGB01";
        String output;
        serializeJson(doc, output);
        server.send(200, "text/json", output);
      }
      else if(cmnd == "Color") {
        if(server.hasArg("c")){
          String color = server.arg("c");
          SetColor(Color(strtoul(color.substring(0,2).c_str(), NULL, 16), strtoul(color.substring(2,4).c_str(), NULL, 16), strtoul(color.substring(4,6).c_str(), NULL, 16)), true);
        }
  
        // They want to know the current color.
        DynamicJsonDocument doc(50);
        Color c = GetColor();
        char cs[6];
        sprintf(cs, "#%02X%02X%02X", c.r, c.g, c.b);
        doc["Color"] = cs;
        String output;
        serializeJson(doc, output);
        server.send(200, "text/json", output);
      }
      else if(cmnd == "Program") {
        if(server.hasArg("p")) {
          // Set the program and settings

          // p=-1 means the user wants the program to stop.
        }

        // Return the program
      }
    }
  });
  server.on("/description.xml", HTTP_GET, [](){
    SSDP.schema(server.client());
  });
  server.begin();
  
  Program_Clear();
}

void HandleWebserver()
{
  server.handleClient();
}

#endif
