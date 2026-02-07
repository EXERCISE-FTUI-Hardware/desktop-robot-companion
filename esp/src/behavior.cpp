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
        sleepIntervalTimer = new Timer(15000);
        touchTimer = new Timer(1000);
        blinkIntervalTimer = new Timer(4000);
        blinkTimer = new Timer(100);
    }

    IdleState::~IdleState() {
        delete sleepIntervalTimer;
        delete touchTimer;
        delete blinkIntervalTimer;
        delete blinkTimer;
    }

    void IdleState::draw() {
        Display::clear();

        if (alwaysOn) {
            Display::drawBitmap(Animations::ALWAYS_ON);
        }

        if (isTouched) {
            Display::drawBitmap(Animations::TOUCHED);
        }
        else if (isBlinking) {
            Display::drawBitmap(Animations::BLINK);
        }
        else {
            Display::drawBitmap(Animations::IDLE);
        }
    }

    void IdleState::enter() {
        sleepIntervalTimer->start();
        blinkIntervalTimer->start();
        draw();
    }

    void IdleState::update() {
        sleepIntervalTimer->update();
        touchTimer->update();
        blinkIntervalTimer->update();
        blinkTimer->update();

        if (TouchSensor::aWasTapped()) {
            alwaysOn = !alwaysOn;

            if (alwaysOn) {
                sleepIntervalTimer->reset();
            }
            else {
                sleepIntervalTimer->start();
            }

            draw();
        }

        if (blinkTimer->isDone()) {
            blinkTimer->reset();
            blinkIntervalTimer->setDuration(5000 + random(-2000, 2000));
            blinkIntervalTimer->start();
            isBlinking = false;
            Display::clear();
            draw();
        }
        
        if (touchTimer->isDone()) {
            touchTimer->reset();
            isTouched = false;
            Display::clear();
            draw();
        }

        if (!isTouched && blinkIntervalTimer->isDone()) {
            blinkIntervalTimer->reset();
            blinkTimer->start();
            isBlinking = true;
            Display::clear();
            draw();
        }

        if (TouchSensor::bWasTapped()) {
            blinkTimer->reset();
            touchTimer->start();
            isTouched = true;
            Display::clear();
            draw();
        }


        if (TouchSensor::aIsHeld()) {
            changeState(new WiFiState());
            return;
        }

        if (sleepIntervalTimer->isDone()) {
            changeState(new SleepState());
            return;
        }
    }
}

namespace Behavior {
    void SleepState::enter() {
        Display::clear();
        Display::drawBitmap(Animations::SLEEP);
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
        if (TouchSensor::aWasTapped()) {
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