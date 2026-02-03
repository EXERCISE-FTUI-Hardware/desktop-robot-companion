#ifndef TOUCHSENSOR_HPP
#define TOUCHSENSOR_HPP

#include <Arduino.h>

namespace TouchSensor {
    //Pin definitions
    static const int touchSensorPin0 = 0;
    static const int touchSensorPin1 = 1;

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
    TouchState getState0();
    TouchState getState1();
    
    // Check if a tap just happened (returns true once per tap)
    bool wasTapped0();
    bool wasTapped1();
    
    // Check if currently being held
    bool isHeld0();
    bool isHeld1();
}

#endif