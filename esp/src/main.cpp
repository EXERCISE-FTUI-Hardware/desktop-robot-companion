#include <Arduino.h>

#include "display.hpp"
#include "animations.hpp"
#include "website.hpp"  
#include "touchsensor.hpp"

static const int32_t SERIAL_SPEED = 115200;

void setup() {
    Serial.begin(SERIAL_SPEED);

    // Wait for Serial to start.
    delay(500);

    Serial.println(F("Hello, world!"));

    Display::initialize();
    Website::initialize();
    TouchSensor::initialize();

    Display::draw(Animations::LOGO);
}

void loop() {
    Website::update();
    TouchSensor::update();

    //display clock for a certain duration when idle
    //screen goes blank and maybe esp sleeps after duration
    //to conserve battery

    if(TouchSensor::A_wasTapped()) {
        //maybe play an animation
        //display clock again for a duration
    }

}