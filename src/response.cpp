#include "response.h"

namespace Response {
void ok(WiFiClient client, String responseBody) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:application/json");
  client.println("Access-Control-Allow-Origin: *");
  client.println("Connection: close");
  client.println();

  client.println(responseBody);
  client.println();
}

void not_found(WiFiClient client) {
  client.println("HTTP/1.1 404 Not Found");
  client.println("Content-type:application/json");
  client.println("Access-Control-Allow-Origin: *");
  client.println("Connection: close");
  client.println();
}

void unauthorized(WiFiClient client) {
  client.println("HTTP/1.1 401 Unauthorized");
  client.println("Content-type:application/json");
  client.println("Access-Control-Allow-Origin: *");
  client.println("Connection: close");
  client.println();
}

void server_error(WiFiClient client) {
  client.println("HTTP/1.1 500 Server Error");
  client.println("Content-type:application/json");
  client.println("Access-Control-Allow-Origin: *");
  client.println("Connection: close");
  client.println();
}
} // namespace Response
