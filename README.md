# Deprecated
Although this works well, the ESP32-CAM chip is a bit weak and somehow volatile (even more for those who don't understand C++ well)
So I'll be migrating this to a RPi + Webcam :smiley:

## Need to create an `auth_info.cpp` file like this inside `src` folder

``` c++
#include "auth_info.h"

namespace AuthInfo {
const char *wifi_ssid = "wifi_ssid";
const char *wifi_password = "wifi_password";
const char *management_password = "management_screen_password";

} // namespace AuthInfo

```

