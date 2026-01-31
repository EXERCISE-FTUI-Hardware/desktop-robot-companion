#ifndef WIFI_HPP
#define WIFI_HPP

#include <Arduino.h>

namespace WiFi {
    const char *ssid = "ESP32";
    const IPAddress ip(192, 168, 0, 1);

    void initialize();
}

#endif