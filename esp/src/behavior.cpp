#include "behavior.hpp"

#include "touchsensor.hpp"
#include "display.hpp"
#include "animations.hpp"
#include "website.hpp"
#include "timer.hpp"

namespace Behavior {
    State *state = nullptr;

    void changeState(State *nextState) {
        if (state != nullptr) {
            state->exit();
            delete state;
        }

        state = nextState;
        state->enter();
    }
}

namespace Behavior {
    void LogoState::enter() {
        Display::drawBitmap(Animations::LOGO);
        delay(2000);
        Display::clear();
        changeState(new IdleState());
    }
}

namespace Behavior {
    bool IdleState::alwaysOn = false;

    IdleState::IdleState() {
        idleTimer = new Timer(10000);
        touchTimer = new Timer(1000);
    }

    IdleState::~IdleState() {
        delete idleTimer;
        delete touchTimer;
    }

    void IdleState::draw() {
        if (alwaysOn) {
            Display::drawBitmap(Animations::ALWAYS_ON);
        }

        if (isTouched) {
            Display::drawBitmap(Animations::TOUCHED);
        }
        else {
            Display::drawBitmap(Animations::IDLE);
        }
    }

    void IdleState::enter() {
        idleTimer->start();
        draw();
    }

    void IdleState::update() {
        idleTimer->update();
        touchTimer->update();

        if (TouchSensor::aWasTapped()) {
            alwaysOn = !alwaysOn;
            draw();
        }
        
        if (touchTimer->isDone()) {
            touchTimer->reset();
            isTouched = false;
            Display::clear();
            draw();
        }

        if (TouchSensor::bWasTapped()) {
            touchTimer->start();
            isTouched = true;
            Display::clear();
            draw();
        }

        if (TouchSensor::aIsHeld()) {
            changeState(new WiFiState());
            return;
        }

        if (idleTimer->isDone()) {
            changeState(new SleepState());
            return;
        }
    }
}

namespace Behavior {
    void SleepState::enter() {
        Display::clear();
    }

    void SleepState::update() {
        if (TouchSensor::bWasTapped()) {
            changeState(new IdleState());
        }
    }

}

namespace Behavior {
    void WiFiState::enter() {
        Website::resume();
    }

    void WiFiState::update() {
        if (TouchSensor::aIsHeld()) {
            changeState(new IdleState());
        }
    }

    void WiFiState::exit() {
        Website::pause();
    }
}

void Behavior::initialize() {
    changeState(new LogoState());
}

void Behavior::update() {
    if (state != nullptr) state->update();
}