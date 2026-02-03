#include "touchsensor.hpp"

namespace TouchSensor {
    //Sensor value when touched is usually 4095 (tested manually)
    static const int touchThreshold = 4000;

    //Hold time threshold and trackers
    static const unsigned long holdTimeThreshold = 500;
    int lastTouchTime0 = 0;
    int lastTouchTime1 = 0;

    //Reset states
    TouchState sensor0 = IDLE;
    TouchState sensor1 = IDLE;

    void initialize() {
        pinMode(touchSensorPin0, INPUT);
        pinMode(touchSensorPin1, INPUT);

    }

        TouchState getState0() {
        return sensor0;
    }
    
    TouchState getState1() {
        return sensor1;
    }
    
    bool wasTapped0() {
        if (sensor0 == TAPPED) {
            sensor0 = IDLE;
            return true;
        }
        return false;
    }
    
    bool wasTapped1() {
        if (sensor1 == TAPPED) {
            sensor1 = IDLE;
            return true;
        }
        return false;
    }
    
    bool isHeld0() {
        return sensor0 == HELD;
    }
    
    bool isHeld1() {
        return sensor1 == HELD;
    }

    void update() {
        //Boolean for if the sensor reading is over the threshold (touched)
        bool isTouched0 = analogRead(touchSensorPin0) > touchThreshold;
        bool isTouched1 = analogRead(touchSensorPin1) > touchThreshold;

        //Sensor 0
        if(isTouched0 && sensor0 == IDLE) {
            sensor0 = TOUCHED;
            lastTouchTime0 = millis();
        }
        else if(isTouched0 && sensor0 == TOUCHED) {
            if(millis() - lastTouchTime0 > holdTimeThreshold) {
                sensor0 = HELD;
            }
        }
        else if(!isTouched0 && sensor0 == TOUCHED) {
            sensor0 = TAPPED;
        }

        //Sensor 1
        if(isTouched1 && sensor1 == IDLE) {
            sensor1 = TOUCHED;
            lastTouchTime1 = millis();
        }
        else if(isTouched1 && sensor1 == TOUCHED) {
            if(millis() - lastTouchTime1 > holdTimeThreshold) {
                sensor1 = HELD;
            }
        }
        else if(!isTouched1 && sensor1 == TOUCHED) {
            sensor1 = TAPPED;
        }
    }
}
