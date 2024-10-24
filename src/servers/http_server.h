#ifndef HTTP_SERVER_H_
#define HTTP_SERVER_H_

#include "Arduino.h"
#include <DHT.h>
#include <WiFi.h>

#include "../response.h"
#include "camera_server.h"

#include "controllers/auth_http_controller.h"
#include "controllers/dht_controller.h"
#include "controllers/gpio_http_controller.h"
#include "controllers/html_controller.h"
#include "controllers/settings_controller.h"
#include "controllers/stream_http_controller.h"

namespace HttpServer {
void handleRequest(WiFiClient client, httpd_handle_t stream_httpd, DHT dht);
} // namespace HttpServer

#endif // HTTP_SERVER_H_
