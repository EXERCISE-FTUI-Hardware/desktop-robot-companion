#ifndef TOUCHSENSOR_HPP
#define TOUCHSENSOR_HPP

#include <Arduino.h>

namespace TouchSensor {
    //Pin definitions
    static const int PIN_A = 32;
    static const int PIN_B = 33;

    //Sensor States
    enum TouchState{
        IDLE,
        TOUCHED,
        TAPPED,
        HELD
    };

    void initialize();
    void update();
    
    // Get current state of each sensor
    TouchState aGetState();
    TouchState bGetState();
    
    // Check if a tap just happened (returns true once per tap)
    bool aWasTapped();
    bool bWasTapped();
    
    // Check if currently being held
    bool aIsHeld();
    bool bIsHeld();
}

#endif