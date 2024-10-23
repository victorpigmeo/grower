#ifndef HTTP_SERVER_H_
#define HTTP_SERVER_H_

#include "Arduino.h"
#include <WiFi.h>

#include "../response.h"
#include "camera_server.h"

namespace HttpServer {
void handleRequest(WiFiClient client, httpd_handle_t stream_httpd);
} // namespace HttpServer

#endif // HTTP_SERVER_H_
