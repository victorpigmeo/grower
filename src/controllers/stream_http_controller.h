#ifndef STREAM_HTTP_CONTROLLER_H_
#define STREAM_HTTP_CONTROLLER_H_

#include "Arduino.h"
#include "esp_http_server.h"
#include <WiFi.h>

#include "../response.h"
#include "servers/camera_server.h"

namespace StreamHttpController {
void handle(WiFiClient client, String url_slices[],
            httpd_handle_t stream_httpd);

} // namespace StreamHttpController

#endif // STREAM_HTTP_CONTROLLER_H_
