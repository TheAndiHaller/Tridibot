// configuraciones para actualizar el firmware por wifi
void otaInit() {
  const char* update_path = "/firmware";
  const char* update_username = "admin";
  const char* update_password = "admin";

  httpUpdater.setup(&server, update_path, update_username, update_password);
}
