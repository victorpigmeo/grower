#include "dht_controller.h"

namespace DHTController {
void handle(WiFiClient client, String url_slices[], DHT dht) {

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float heat_index = dht.computeHeatIndex(temperature, humidity, false);

  if (isnan(temperature) || isnan(humidity) || isnan(heat_index)) {
    Response::server_error(client);
  } else {
    Response::ok(client, "{\"temperature\": " + String(temperature) +
                             ", \"humidity\": " + String(humidity) +
                             ", \"heat_index\": " + String(heat_index) + " }");
  }
}
} // namespace DHTController
