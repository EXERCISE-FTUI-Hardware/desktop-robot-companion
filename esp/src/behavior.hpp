#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

#include <Arduino.h>

#include "timer.hpp"

namespace Behavior {
    class State {
        public:
        virtual ~State() = default;
        virtual void enter() {};
        virtual void update() {};
        virtual void exit() {};
    };

    class LogoState : public State {
        public:
        void enter() override;
    };

    class IdleState : public State {
        private:
        static bool alwaysOn;
        bool isTouched = false;
        bool isBlinking = false;

        Timer *sleepIntervalTimer = nullptr;
        Timer *touchTimer = nullptr;
        Timer *blinkIntervalTimer = nullptr;
        Timer *blinkTimer = nullptr;

        inline void draw();

        public:
        IdleState();
        ~IdleState() override;
        void enter() override;
        void update() override;
    };

    class SleepState : public State {
        public:
        void enter() override;
        void update() override;
    };

    class WiFiState : public State {
        public:
        void enter() override;
        void update() override;
        void exit() override;
    };

    // in ms
    const unsigned long IDLE_TIME_BEFORE_SLEEP = 6000;

    void initialize();
    void update();
}

#endif // BEHAVIOR_HPP