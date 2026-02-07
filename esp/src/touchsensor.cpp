#include "touchsensor.hpp"

namespace TouchSensor {
    //Sensor value when touched is usually 4095 (tested manually)
    static const int touchThreshold = 4000;

    //Hold time threshold and trackers
    static const unsigned long holdTimeThreshold = 500;
    int lastTouchTimeA = 0;
    int lastTouchTimeB = 0;

    //Reset states
    TouchState sensorA = IDLE;
    TouchState sensorB = IDLE;

    void initialize() {
        pinMode(PIN_A, INPUT);
        pinMode(PIN_B, INPUT);

    }

    TouchState aGetState() {
        return sensorA;
    }
    
    TouchState bGetState() {
        return sensorB;
    }
    
    bool aWasTapped() {
        if (sensorA == TAPPED) {
            sensorA = IDLE;
            return true;
        }
        return false;
    }
    
    bool bWasTapped() {
        if (sensorB == TAPPED) {
            sensorB = IDLE;
            return true;
        }
        return false;
    }
    
    bool aIsHeld() {
        return sensorA == HELD;
    }
    
    bool bIsHeld() {
        return sensorB == HELD;
    }

    void update() {
        //Boolean for if the sensor reading is over the threshold (touched)
        bool isTouchedA = analogRead(PIN_A) > touchThreshold;
        bool isTouchedB = analogRead(PIN_B) > touchThreshold;

        //Sensor A
        if(isTouchedA && sensorA == IDLE) {
            sensorA = TOUCHED;
            lastTouchTimeA = millis();
        }
        else if(isTouchedA && sensorA == TOUCHED) {
            if(millis() - lastTouchTimeA > holdTimeThreshold) {
                sensorA = HELD;
            }
        }
        else if(!isTouchedA && sensorA == TOUCHED) {
            sensorA = TAPPED;
        }
        else if(!isTouchedA && sensorA == HELD) {
            sensorA = IDLE;
        }

        //Sensor B
        if(isTouchedB && sensorB == IDLE) {
            sensorB = TOUCHED;
            lastTouchTimeB = millis();
        }
        else if(isTouchedB && sensorB == TOUCHED) {
            if(millis() - lastTouchTimeB > holdTimeThreshold) {
                sensorB = HELD;
            }
        }
        else if(!isTouchedB && sensorB == TOUCHED) {
            sensorB = TAPPED;
        }
        else if(!isTouchedB && sensorB == HELD) {
            sensorB = IDLE;
        }
    }
}
