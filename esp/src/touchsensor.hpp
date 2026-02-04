#ifndef TOUCHSENSOR_HPP
#define TOUCHSENSOR_HPP

#include <Arduino.h>

namespace TouchSensor {
    //Pin definitions
    static const int touchSensorAPin = 0;
    static const int touchSensorBPin = 1;

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
    TouchState A_getState();
    TouchState B_getState();
    
    // Check if a tap just happened (returns true once per tap)
    bool A_wasTapped();
    bool B_wasTapped();
    
    // Check if currently being held
    bool A_isHeld();
    bool B_isHeld();
}

#endif