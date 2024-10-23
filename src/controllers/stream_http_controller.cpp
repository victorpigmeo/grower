#include "stream_http_controller.h"

namespace StreamHttpController {
void startStream() { Serial.println("Start stream"); }

void handle(WiFiClient client, String url_slices[],
            httpd_handle_t stream_httpd) {
  String action = url_slices[2];

  if (action == "on") {
    CameraServer::startCamera();
    CameraServer::startStream(stream_httpd);

    Response::ok(client, "{\"stream\": \"on\"}");
  } else if (action == "off") {
    CameraServer::stopStream(stream_httpd);

    Response::ok(client, "{\"stream\": \"off\"}");
  } else {
    Response::not_found(client);
  }
}

} // namespace StreamHttpController
