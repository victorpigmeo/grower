#include "gpio_http_controller.h"

namespace GPIOHttpController {
void handle(WiFiClient client, String url_slices[]) {
  if (SPIFFS.exists("/auth") != 0) {
    String action = url_slices[2];
    int pin = url_slices[3].toInt();
    int value = url_slices[4].toInt();

    Serial.print("Action: ");
    Serial.print(action);
    Serial.print(" | PIN: ");
    Serial.print(pin);
    Serial.print(" | Value: ");
    Serial.println(value);

    if (action == "analog") {
      analogWrite(pin, value);
    } else if (action == "digital") {
      digitalWrite(pin, value);
    } else {
      Response::not_found(client);
      return;
    }

    Response::ok(client, "{\"pin\": " + String(pin) +
                             ", \"value\": " + String(value) + "}");
  } else {
    Response::unauthorized(client);
  }
}
} // namespace GPIOHttpController
