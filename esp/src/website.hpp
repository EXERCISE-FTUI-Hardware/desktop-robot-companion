#ifndef WEBSITE_HPP
#define WEBSITE_HPP

#include <Arduino.h>

namespace Website {
    static const char *ssid = "ESP32";
    static const IPAddress apIp(8, 8, 8, 8);
    static const IPAddress apMask(255, 255, 255, 0);

    void initialize();
    void update();
}

#endif