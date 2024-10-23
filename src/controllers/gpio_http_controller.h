#ifndef GPIO_HTTP_CONTROLLER_H_
#define GPIO_HTTP_CONTROLLER_H_

#include "SPIFFS.h"
#include <Arduino.h>
#include <WiFi.h>

#include "../response.h"

namespace GPIOHttpController {
void handle(WiFiClient client, String url_slices[]);
}

#endif // GPIO_HTTP_CONTROLLER_H_
