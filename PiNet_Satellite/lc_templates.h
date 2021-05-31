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
  return "<div id='picker' style='width:300px;margin:0 auto 50px auto;'></div></p>"
         "<script>function doRequest(e){var o='/cm?cmnd=Color';null!=e&&(o+='&c='+e);var r=new XMLHttpRequest;r.onreadystatechange=function(){4==r.readyState&&200==r.status&&(colorPicker.color.hexString=JSON.parse(r.responseText).Color)},r.open('GET',o),r.send(null)}</script>"
         "<script>var colorPicker = new iro.ColorPicker('#picker');colorPicker.on('input:end', function(color){console.log(color.hexString);doRequest(color.hexString.substring(1));});</script>"
         "<script>setInterval(doRequest,1000);</script>";
}

#endif
