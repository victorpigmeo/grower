#ifndef DHT_CONTROLLER_H_
#define DHT_CONTROLLER_H_

#include "Arduino.h"
#include <DHT.h>
#include <WiFi.h>

#include "../response.h"

namespace DHTController {

void handle(WiFiClient client, String url_slices[], DHT dht);

}
#endif // DHT_CONTROLLER_H_
