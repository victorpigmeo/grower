#ifndef AUTH_HTTP_CONTROLLER_H_
#define AUTH_HTTP_CONTROLLER_H_

#include "SPIFFS.h"
#include <Arduino.h>
#include <WiFi.h>

#include "../auth_info.h"
#include "../response.h"

namespace AuthHttpController {
void handle(WiFiClient client, String url_slices[]);
}

#endif // AUTH_HTTP_CONTROLLER_H_
