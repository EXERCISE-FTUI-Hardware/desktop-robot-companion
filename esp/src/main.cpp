#include <Arduino.h>

#include "display.hpp"
#include "animations.hpp"
#include "website.hpp"  
#include "touchsensor.hpp"
#include "behavior.hpp"

static const int32_t SERIAL_SPEED = 9600;

void setup() {
    Serial.begin(SERIAL_SPEED);

    // Wait for Serial to start.
    delay(500);

    Serial.println(F("Hello, world!"));

    Display::initialize();
    Website::initialize();
    TouchSensor::initialize();
    Behavior::initialize();
}

void loop() {
    Website::update();
    TouchSensor::update();
    Behavior::update();

    delay(50);
}