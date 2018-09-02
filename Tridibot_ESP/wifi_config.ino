
void updateConfigFile(String value) {
  DynamicJsonBuffer jsonBuffer;
  String input;

  File file = SPIFFS.open("/config.json", "r");
  if (file) {
    while (file.available()) {
      input = file.readString();
    }
    file.close();
    JsonObject& conf = jsonBuffer.parseObject(input);

    conf["AP_SSID"] = value;

    SPIFFS.remove("/config.json");
    file = SPIFFS.open("/config.json", "w");
    conf.prettyPrintTo(file);
    file.close();
    connectionConfig();
  }
}

void updateConfigFile(String ssid, String pass) {
  DynamicJsonBuffer jsonBuffer;
  String input;

  File file = SPIFFS.open("/config.json", "r");
  if (file) {
    while (file.available()) {
      input = file.readString();
    }
    file.close();
    JsonObject& conf = jsonBuffer.parseObject(input);

    conf["WIFI_SSID"] = ssid;
    conf["WIFI_PASSWORD"] = pass;

    SPIFFS.remove("/config.json");
    file = SPIFFS.open("/config.json", "w");
    conf.prettyPrintTo(file);
    file.close();
    connectionConfig();
  }

}

void connectionConfig() {
  WiFi.disconnect();
  delay(500);
  DynamicJsonBuffer jsonBuffer;
  String input;
  File file = SPIFFS.open("/config.json", "r");

  while (file.available()) {
    input = file.readString();
  }
  file.close();
  JsonObject& conf = jsonBuffer.parseObject(input);
  String wifissid = conf["WIFI_SSID"];
  String wifipass = conf["WIFI_PASSWORD"];

  String AuxbotName = conf["AP_SSID"];
  botName = AuxbotName;
  
  const char* AP_SSID = conf["AP_SSID"];
  const char* AP_PASSWORD = conf["AP_PASSWORD"];
  const char* WIFI_SSID = conf["WIFI_SSID"];
  const char* WIFI_PASSWORD = conf["WIFI_PASSWORD"];

  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(AP_SSID, AP_PASSWORD);
  IPAddress myIP = WiFi.softAPIP();

  long msBefore = millis();
  boolean connecting = true;

  if (wifissid.length() == 0 || wifipass.length() == 0) {
  } else {
    WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  }
  while (connecting) {
    if (millis() - msBefore > 10000) {
      connecting = false;
      //WiFiMulti.run();
    }

    if (WiFiMulti.run() == WL_CONNECTED) {
      connecting = false;
    }
    yield();
  }
}
