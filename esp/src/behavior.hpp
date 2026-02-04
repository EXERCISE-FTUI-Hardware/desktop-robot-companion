#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

#include <Arduino.h>

namespace Behavior {
    class State {
        protected:
        State() {}

        public:
        void enter() {}
        void update() {}
        void exit() {}
    };

    class Timer {
        private:
        unsigned long duration;
        unsigned long elapsed = 0;
        unsigned long last;
        bool isPaused = false;

        public:
        Timer(unsigned long duration) : duration(duration), last(millis()) {}

        void tick();
        void pause();
        void resume();
        bool done();
    };

    // in ms
    const unsigned long IDLE_TIME_BEFORE_SLEEP = 6000;

    void update();
}

#endif // BEHAVIOR_HPP