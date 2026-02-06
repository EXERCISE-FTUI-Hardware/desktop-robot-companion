#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

#include <Arduino.h>

namespace Behavior {
    enum State {
        LOGO,
        IDLE,
        SLEEP,
        WIFI
    };

    // in ms
    const unsigned long IDLE_TIME_BEFORE_SLEEP = 6000;

    void initialize();
    void update();
}

#endif // BEHAVIOR_HPP