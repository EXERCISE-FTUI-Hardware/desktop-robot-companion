#include "behavior.hpp"

#include "touchsensor.hpp"
#include "display.hpp"
#include "animations.hpp"

namespace Behavior {
    State state = LogoState();
    
    void changeState(State nextState) {
        state.exit();
        state = nextState;
        state.enter();
    };

    void LogoState::enter() {
        Display::clear();
        Display::draw(Animations::LOGO);
        delay(1000);
        Display::clear();
        
        // changeState(IdleState());
    }  

    void IdleState::enter() {
        idleTimer = new Timer(IDLE_TIME_BEFORE_SLEEP);
    }

    void IdleState::update() {
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

    void IdleState::exit() {
        delete idleTimer;
    }

    bool IdleState::alwaysOn = false;

    void SleepState::enter() {
        Display::clear();
    }

    void SleepState::update() {
        if (TouchSensor::B_wasTapped()) {
            changeState(IdleState());
        }
    }

    void WiFiState::enter()  {
        Display::draw(Animations::LOGO);
    }

    void WiFiState::update() {

    }

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
}

void Behavior::update() {
    state.update();
}