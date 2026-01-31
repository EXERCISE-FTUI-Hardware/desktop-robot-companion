#include <Arduino.h>

#include "display.hpp"
#include "animation_data.hpp"
#include "wifi.hpp"

static const int32_t SERIAL_SPEED = 115200;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(SERIAL_SPEED);

    // Wait for Serial to start.
    delay(500);

    Serial.println(F("Hello, world!"));

    Display::initialize();
    WiFi::initialize();

    Display::draw(Bitmaps::LOGO);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}