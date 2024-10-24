#include "SPIFFS.h"
#include <DHT.h>
#include <WiFi.h>

#include "auth_info.h"
#include "servers/camera_server.h"
#include "servers/http_server.h"

// Aux pins
#define FLASH_PIN 4
#define DHT_PIN 16

// Camera server instance
httpd_handle_t stream_httpd = NULL;

// HttpServer instance
WiFiServer server(8080);

// DHT Instance
DHT dht(DHT_PIN, DHT11);

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // deactivate brownout

  Serial.begin(115200);
  Serial.setDebugOutput(false);

  dht.begin();

  pinMode(12, OUTPUT);

  // Connect WiFi
  Serial.print("Connecting to ");
  Serial.print(AuthInfo::wifi_ssid);
  WiFi.begin(AuthInfo::wifi_ssid, AuthInfo::wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP Address: ");
  Serial.print(WiFi.localIP());
  Serial.println();

  // Start HTTP Server
  server.begin();

  // Start file manager
  if (!SPIFFS.begin(true)) {
    Serial.println("An error has ocurred while mounting SPIFFS");
    return;
  }
}

void loop() {
  WiFiClient client = server.available();

  if (client) {

    HttpServer::handleRequest(client, stream_httpd, dht);

    client.stop();
  }
}
