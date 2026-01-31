#include "wifi.hpp"

#include <WiFi.h>

void WiFi::initialize() {
    Serial.println(F("Initializing WiFi AP..."));

    WiFi.softAPConfig(ip, INADDR_NONE, INADDR_NONE);
    WiFi.softAP(ssid);

    Serial.print(F("AP address is "));
    Serial.println(WiFi.softAPIP());
}