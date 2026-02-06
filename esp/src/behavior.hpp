#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

#include <Arduino.h>

namespace Behavior {
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
    
    class State {
        protected:
        State() {}

        public:
        void enter() {}
        void update() {}
        void exit() {}
    };

    class LogoState : public State {
        public:
        void enter();
    };

    class IdleState : public State {
        private:
        static bool alwaysOn;
        Timer *idleTimer;

        public:
        void enter();
        void update();
        void exit();
    };

    class SleepState : public State {
        public:
        void enter();
        void update();
    };

    class WiFiState : public State {
        public:
        void enter();
        void update();
    };

    // in ms
    const unsigned long IDLE_TIME_BEFORE_SLEEP = 6000;

    void update();
}

#endif // BEHAVIOR_HPP