#ifndef LC_TEMPLATES
#define LC_TEMPLATES

#include "lc_settings.h"

String FrontMatter() {
  return "<!DOCTYPE html><html>"
         "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
         "<script src='https://cdn.jsdelivr.net/npm/@jaames/iro@5'></script>"
         "<link rel=\"icon\" href=\"data:,\">"
         "<style>"
         "html { background-color:#252525; color:#eaeaea; font-family:Helvetica; margin:0px auto; text-align:center;}"
         ".button1 { background-color:#32a852; color:#eaeaea; border:none; border-radius:5px; padding:10px 0px; width:100%; font-size:16px; margin-bottom:2px; cursor:pointer;}"
         ".button2 { background-color:#a83232; color:#eaeaea; border:none; border-radius:5px; padding:10px 0px; width:100%; font-size:16px; margin-bottom:2px; cursor:pointer;}"
         ".button3 { background-color:#5e7364;}"
         "</style>"
         "</head><body>"
         "<div style='display:inline-block; text-align:center; max-width:350px;'>";
}

String HeadMatter() {
  return String("<h2>PiNet Satellite</h2>") + "<h1>" + conf.friendly_name + "</h1>";
}

String ButtonMatter(String url, String text) {
  return "<p><a href=\"" + url +  "\"><button class=\"button1\">" + text + "</button></a></p>";
}

String InfoHeader(String head) {
  return "<h3>" + head + "</h3>";
}

String InfoRow(String key, String value) {
  return "<p style='width:100%;'><div style='width:50%;display:inline-block;text-align:left;'>" + key + "</div><div style='width:50%;display:inline-block;text-align:left;'>" + value + "</div></p>";
}

String BackMatter() {
  return "<p><button class=\"button2\" onclick=\"if(confirm('Are you sure you want to restart?')){window.location.assign('/restart')};\">Restart</button></p>"
         "<hr/>"
         "<div style='width:100%; font-size:10pt; text-align:right;'>PiNet 0.1 by raimund89</div>"
         "</div></body></html>";
}

String PickerMatter() {
  return "<div id='colorpicker' style='width:300px;margin:0 auto 50px auto;'></div><div id='whitepicker' style='width:300px;margin:0 auto 50px auto;'></div></p>"
         "<script>"
         "var connection=new WebSocket('ws://' + location.hostname + ':81/');"
         "connection.onopen=function(){connection.send('C');};"
         "connection.onmessage=function(e){"
         "    colorPicker.color.hexString=e.data.substring(0,7);"
         "    whitePicker.color.hexString='#'+e.data.substring(7).repeat(3);"
         "};"
         "var n = Date.now();"
         "function sendcolor(){"
         "    if(Date.now()-n<125){return;}"
         "    n=Date.now();"
         "    connection.send('#'+colorPicker.color.hexString.substring(1)+whitePicker.color.hexString.substring(1,3));"
         "}"
         "var colorPicker = new iro.ColorPicker('#colorpicker');"
         "colorPicker.on('input:change', function(color){console.log(color.hexString);sendcolor();});"
         "var whitePicker = new iro.ColorPicker('#whitepicker',{layout:[{component:iro.ui.Slider,options:{sliderType:'value'}}]});"
         "whitePicker.on('input:change', function(color){console.log(color.hexString);sendcolor();});"
         "</script>";
}

#endif
