#include "auth_http_controller.h"

namespace AuthHttpController {

void handle(WiFiClient client, String url_slices[]) {

  String action = url_slices[2];
  String password = url_slices[3];

  File auth_file = SPIFFS.open("/auth", "w");

  if (action == "unlock") {
    if (password == AuthInfo::management_password) {

      auth_file.print("authorized");
      Response::ok(client, "{\"unlocked\": true}");
    } else {
      Response::unauthorized(client);
    }
  } else if (action == "lock") {
    SPIFFS.remove("/auth");
    Response::ok(client, "{\"locked\": true}");
  } else {
    Response::not_found(client);
  }

  auth_file.close();
}

} // namespace AuthHttpController
