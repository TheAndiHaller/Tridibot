// configuraciones para actualizar el firmware por wifi
void otaInit() {
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
      SPIFFS.end();   // Unmount FS using LittleFS.end()
    }
  });

  ArduinoOTA.begin();
}
