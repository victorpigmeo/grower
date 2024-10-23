#include "html_controller.h"

namespace HTMLController {
void renderPage(WiFiClient client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println();

  File file = SPIFFS.open("/index.html");

  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  while (file.available()) {
    client.write(file.read());
  }

  file.close();
  client.println();
}
} // namespace HTMLController
