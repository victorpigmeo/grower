#ifndef SETTINGS_CONTROLLER_H_
#define SETTINGS_CONTROLLER_H_

#include "SPIFFS.h"
#include <Arduino.h>
#include <WiFi.h>

namespace SettingsController {
void handle(WiFiClient client, String url_slices[]);
}

#endif // SETTINGS_CONTROLLER_H_
