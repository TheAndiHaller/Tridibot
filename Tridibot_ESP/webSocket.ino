
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:

      com = "S";
      clientCont--;
      break;
    case WStype_CONNECTED: {
        IPAddress ip = webSocket.remoteIP(num);
        //webSocket.sendTXT(num, "Connected");
        clientCont++;
      }
      break;
    case WStype_TEXT:

      String incom = (char*)payload;
      if (incom.startsWith("conf_AP:")) {
        incom.substring(8);
        updateConfigFile(incom.substring(8));

      } else if (incom.startsWith("conf_WiFi:")) {
        int passIndex = incom.indexOf("pass:");
        incom.substring(10, passIndex);
        incom.substring((passIndex + 5));
        updateConfigFile(incom.substring(10, passIndex), incom.substring((passIndex + 5)));

      } else if (incom.startsWith("conf_Led:")) {
        String sub  = incom.substring(9);
        Serial.write('b');
        for (int i = 0; i < sub.length(); i++) {
          Serial.write(sub[i]);
        }
      } else if (incom.equals("update")) {
        IPAddress myIP = WiFi.localIP();
        String mes = "Tu IP es: ";
        mes +=  myIP.toString().c_str();
        webSocket.sendTXT(num, mes);

      } else if (incom.equals("info")) {
        String info = "nom" + botName;
        info += " vel" + actSpeed;
        info += " col" + actColor;
        info += " mot" + motorStatus;

        webSocket.sendTXT(num, info);

      } else if (incom.startsWith("P")) {
        progMode = true;
        com = incom[1];

      } else {
        com = incom;
        clientID = num;
      }

      break;
  }
}
