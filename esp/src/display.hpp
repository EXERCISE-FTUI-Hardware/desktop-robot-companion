#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <Arduino.h>

namespace Display {
    static const uint8_t DISPLAY_WIDTH = 128;
    static const uint8_t DISPLAY_HEIGHT = 64;
    
    void initialize();
    void draw(const uint8_t bitmap[DISPLAY_WIDTH * DISPLAY_HEIGHT]);
}

#endif