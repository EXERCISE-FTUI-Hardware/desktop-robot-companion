#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <Arduino.h>

namespace Display {
    static const uint8_t DISPLAY_WIDTH = 128;
    static const uint8_t DISPLAY_HEIGHT = 64;

    static const int8_t DISPLAY_RESET_PIN = -1;
    
    void initialize();
    void clear();
    void drawBitmap(const uint8_t bitmap[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8]);
}

#endif