#ifndef HTMLCONTROLLER_H_
#define HTMLCONTROLLER_H_

#include "SPIFFS.h"
#include <Arduino.h>
#include <WiFi.h>

namespace HTMLController {
void renderPage(WiFiClient client);
}

#endif // HTMLCONTROLLER_H_
