#ifndef WEBSITE_HPP
#define WEBSITE_HPP

#include <Arduino.h>

namespace Website {
    static const char *ssid = "ESP32";
    static const IPAddress ip(192, 168, 0, 1);

    void initialize();
    void update();
}

#endif