void handleServer() {

  server.on("/list", HTTP_GET, handleFileList);
  //load editor
  server.on("/edit", HTTP_GET, []() {
    if (!handleFileRead("/edit.htm")) server.send(404, "text/plain", "FileNotFound");
  });
  //create file
  server.on("/edit", HTTP_PUT, handleFileCreate);
  //delete file
  server.on("/edit", HTTP_DELETE, handleFileDelete);
  //first callback is called after the request has ended with all parsed arguments
  //second callback handles file uploads at that location
  server.on("/edit", HTTP_POST, []() {
    server.send(200, "text/plain", "");
  }, handleFileUpload);

  server.on("/", []() {
    File file = SPIFFS.open("/manual.html.gz", "r");
    if (file) {
      server.streamFile(file, "text/html");
      file.close();
    } else {
      server.send(200, "text/html", "SPIFFS error - File not found!");
    }
  });

  server.on("/config.html", []() {
    File file = SPIFFS.open("/config.html.gz", "r");
    if (file) {
      server.streamFile(file, "text/html");
      file.close();
    } else {
      server.send(200, "text/html", "SPIFFS error - File not found!");
    }
  });

  server.on("/program.html", []() {
    File file = SPIFFS.open("/program.html.gz", "r");
    if (file) {
      server.streamFile(file, "text/html");
      file.close();
    } else {
      server.send(200, "text/html", "SPIFFS error - File not found!");
    }
  });

  server.on("/css/bootstrap.min.css", []() {
    File file = SPIFFS.open("/css/bootstrap.min.css.gz", "r");
    if (file) {
      server.streamFile(file, "text/css");
      file.close();
    } else {
      server.send(200, "text/html", "SPIFFS error - File not found!");
    }
  });

  server.on("/css/my-style.css", []() {
    File file = SPIFFS.open("/css/my-style.css.gz", "r");
    if (file) {
      server.streamFile(file, "text/css");
      file.close();
    } else {
      server.send(200, "text/html", "SPIFFS error - File not found!");
    }
  });

    server.on("/js/bootstrap.min.js", []() {
    File file = SPIFFS.open("/js/bootstrap.min.js.gz", "r");
    if (file) {
      server.streamFile(file, "application/javascript");
      file.close();
    } else {
      server.send(200, "text/html", "SPIFFS error - File not found!");
    }
  });

    server.on("/js/popper.min.js", []() {
    File file = SPIFFS.open("/js/popper.min.js.gz", "r");
    if (file) {
      server.streamFile(file, "application/javascript");
      file.close();
    } else {
      server.send(200, "text/html", "SPIFFS error - File not found!");
    }
  });

  //server.serveStatic("/css/bootstrap.min.css", SPIFFS, "/css/bootstrap.min.css.gz", "max-age=86400");
  //server.serveStatic("/css/my-style.css", SPIFFS, "/css/my-style.css", "max-age=86400");
  //server.serveStatic("/js/bootstrap.min.js", SPIFFS, "/js/bootstrap.min.js", "max-age=86400");
  server.serveStatic("/js/jquery-3.2.1.min.js", SPIFFS, "/js/jquery-3.2.1.min.js", "max-age=86400");
  //server.serveStatic("/js/popper.min.js", SPIFFS, "/js/popper.min.js", "max-age=86400");
  
  server.serveStatic("/fonts/fontawesome.woff2", SPIFFS, "/fonts/fontawesome.woff2", "max-age=86400");
  
  server.serveStatic("/img/run.png", SPIFFS, "/img/run.png", "max-age=86400");
  server.serveStatic("/img/walk-sm.png", SPIFFS, "/img/walk-sm.png", "max-age=86400");
  server.serveStatic("/img/barra-lg.png", SPIFFS, "/img/barra-lg.png", "max-age=86400");
  server.serveStatic("/img/tridibot-sm.png", SPIFFS, "/img/tridibot-sm.png", "max-age=86400");
  server.serveStatic("/favicon.ico", SPIFFS, "/favicon.ico", "max-age=86400");
  server.begin();
}
