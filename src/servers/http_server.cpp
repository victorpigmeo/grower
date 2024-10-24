#include <Arduino.h>

#include "http_server.h"

namespace HttpServer {

void handleRequest(WiFiClient client, httpd_handle_t stream_httpd, DHT dht) {
  String current_line = "";
  String request;

  while (client.connected()) { // loop while the client's connected
    if (client.available()) {
      char c = client.read();

      if (c == '\n') {
        if (current_line.length() == 0) {
          // Handle request
          // Serial.println(request);

          if (request.indexOf("/api/") > 0) {

            char req_array[128];
            char delimiter[] = " ";
            // slices[0] -> method
            // slices[1] -> url
            // slices[2] -> protocol
            String slices[3];

            request.toCharArray(req_array, sizeof(req_array));
            int i = 0;
            String slice = strtok(req_array, delimiter);

            while (slice && i < 3) {
              slices[i] = slice;
              slice = strtok(NULL, delimiter);
              ++i;
            }

            String url = slices[1];
            Serial.print("URL: ");
            Serial.println(url);

            char url_array[128];
            char url_delimiter[] = "/";

            //   // url_slices[0] -> api
            //   // url_slices[1] -> controller
            //   // url_slices[2] -> action(gpio,unlock,settings)/state(stream)
            //   // url_slices[3] -> pin(gpio)/password(unlock)/value(settings)
            //   // url_slices[4] -> value
            String url_slices[5];

            url.toCharArray(url_array, sizeof(url_array));
            int j = 0;
            String url_slice = strtok(url_array, url_delimiter);

            while (url_slice && j < 5) {
              url_slices[j] = url_slice;
              url_slice = strtok(NULL, url_delimiter);
              ++j;
            }

            String controller = url_slices[1];

            if (controller == "stream") {
              StreamHttpController::handle(client, url_slices, stream_httpd);
            } else if (controller == "gpio") {
              GPIOHttpController::handle(client, url_slices);
            } else if (controller == "auth") {
              AuthHttpController::handle(client, url_slices);
            } else if (controller == "settings") {
              SettingsController::handle(client, url_slices);
            } else if (controller == "dht") {
              DHTController::handle(client, url_slices, dht);
            } else {
              Response::not_found(client);
            }

            client.println();
            break;
          }

          HTMLController::renderPage(client);
          break;
        } else {
          current_line = "";
        }
      } else if (c != '\r') {
        request += c;
      }
    }
  }
  request = "";
}

} // namespace HttpServer
