#ifndef RESPONSE_H_
#define RESPONSE_H_

#include "Arduino.h"
#include <WiFi.h>

namespace Response {
void ok(WiFiClient client, String responseBody);
void not_found(WiFiClient client);
void unauthorized(WiFiClient client);
void server_error(WiFiClient client);
} // namespace Response

#endif // RESPONSE_H_
