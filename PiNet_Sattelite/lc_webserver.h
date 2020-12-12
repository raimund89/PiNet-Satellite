#ifndef LC_WEBSERVER
#define LC_WEBSERVER

#include <ESP8266SSDP.h>
#include <ESP8266WebServer.h>
#include <ESP8266SSDP.h>
#include <ArduinoJson.h>

#include "lc_gpio.h"
#include "lc_templates.h"

ESP8266WebServer server(80);

void InitWebserver()
{
  server.on("/", []() {
    server.send(200, "text/html", FrontMatter() + HeadMatter() + ButtonMatter("/description.xml", "SSDP Info") + BackMatter());
    // User wants some device info:
    /*DynamicJsonDocument doc(200);
    doc["ip"] = WiFi.localIP().toString();
    doc["mac"] = WiFi.macAddress();
    doc["hostname"] = WiFi.hostname();
    doc["wifistatus"] = WiFi.status();
    String output;
    serializeJson(doc, output);
    
    server.send(200, "text/json", output);*/
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

  SSDP.setSchemaURL("description.xml");
  SSDP.setHTTPPort(80);
  SSDP.setName("PiNet Sattelite");
  SSDP.setSerialNumber(ESP.getChipId());
  SSDP.setURL("index.html");
  SSDP.setModelName("RGB");
  SSDP.setModelNumber("01");
  SSDP.setManufacturer("PiNet");
  SSDP.begin();
  
  Program_Clear();
}

void HandleWebserver()
{
  server.handleClient();
}

#endif
