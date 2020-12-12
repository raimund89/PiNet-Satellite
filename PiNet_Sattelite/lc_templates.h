#ifndef LC_TEMPLATES
#define LC_TEMPLATES

String FrontMatter() {
  return "<!DOCTYPE html><html>"
         "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
         "<link rel=\"icon\" href=\"data:,\">"
         "<style>"
         "html { background-color: #252525; color: #eaeaea; font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}"
         ".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}"
         ".button2 {background-color: #77878A;}"
         "</style>"
         "</head><body>"
         "<div style='min-width:350px;'>";
}

String HeadMatter() {
  return "<h2>PiNet Sattelite</h2>"
         "Christmas Fractal Lamp";
}

String ButtonMatter() {
  
}

String BackMatter() {
  return "<hr/>"
         "<span style='align:right;'>PiNet 0.1 by raimund89</div>"
         "</div></body></html>";
}

#endif
