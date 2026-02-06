#include "display.hpp"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

namespace Display {
    Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, DISPLAY_RESET_PIN);
}

void Display::initialize() {
    Serial.println(F("Initializing display..."));
    
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("Display allocation failed!"));
        while (true);
    }

    Serial.println(F("Display is up."));

    display.clearDisplay();
    display.display();
}

void Display::clear() {
    display.clearDisplay();
    display.display();
}

void Display::drawBitmap(const uint8_t bitmap[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8]) {
    display.drawBitmap(0, 0, bitmap, DISPLAY_WIDTH, DISPLAY_HEIGHT, 1);
    display.display();
}
