#include "behavior.hpp"

#include "touchsensor.hpp"
#include "display.hpp"
#include "animations.hpp"

namespace Behavior {
    void changeState(State nextState) {
        state.exit();
        state = nextState;
        state.enter();
    };

    class LogoState : public State {
        public:
        void enter() {
            Display::draw(Animations::LOGO);
            delay(1000);
            
            changeState(IdleState());
        }        
    };

    class IdleState : public State {
        private:
        static bool alwaysOn;
        Timer *idleTimer;

        public:
        void enter() {
            idleTimer = new Timer(IDLE_TIME_BEFORE_SLEEP);
        }

        void update() {
            if (TouchSensor::A_wasTapped()) {
                alwaysOn = !alwaysOn;
            }

            if (alwaysOn) {
                idleTimer->pause();
            }
            else {
                idleTimer->resume();
            }

            if (idleTimer->done()) {
                changeState(SleepState());
            }
        }

        void exit() {
            delete idleTimer;
        }
    };

    bool IdleState::alwaysOn = false;

    class SleepState : public State {
        public:
        void enter() {
            Display::clear();
        }

        void update() {
            if (TouchSensor::B_wasTapped()) {
                changeState(IdleState());
            }
        }
    };

    class WiFiState : public State {
        public:
        void enter() {
            Display::draw(Animations::LOGO);
        }

        void update() {

        }
    };

    bool Timer::done() {
        return elapsed > duration;
    }

    void Timer::tick() {
        if (isPaused) {
            last = millis();
            return;
        }

        unsigned long now = millis();
        elapsed += now - last;
        last = now;

        if (done()) {
            pause();
        }
    }

    void Timer::pause() {
        isPaused = true;
    }

    void Timer::resume() {
        isPaused = false;
    }

    State state = LogoState();
}



void Behavior::update() {
    state.update();
}