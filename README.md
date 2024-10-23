## Need to create a auth_info.h file like this inside `src` folder

``` c++
#ifndef AUTH_INFO_H_
#define AUTH_INFO_H_

namespace AuthInfo {
const char *wifi_ssid = "wifi-ssid";
const char *wifi_password = "wifi-password";
const char *management_password = "management-screen-password";
} // namespace AuthInfo

#endif // AUTH_INFO_H_

```

