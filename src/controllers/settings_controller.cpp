#include "settings_controller.h"

namespace SettingsController {
void handle(WiFiClient client, String url_slices[]) {

  if (SPIFFS.exists("/auth") != 0) {
    String action = url_slices[2];
    if (action == "restart") {
      ESP.restart();
    }
  }
}
} // namespace SettingsController
