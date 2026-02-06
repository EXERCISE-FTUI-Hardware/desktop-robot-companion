#include "behavior.hpp"

#include "touchsensor.hpp"
#include "display.hpp"
#include "animations.hpp"

namespace Behavior {
    static State state = LOGO;

    static bool alwaysOn = false;

    void changeState(State nextState);

    void stateEnter(State state) {
        using namespace Display;

        switch (state) {
            case LOGO:
                Display::drawBitmap(Animations::LOGO);
                break;
            case IDLE:
                break;
            case SLEEP:
                Display::clear();
                break;
            default:
                break;
        };
    }

    void stateUpdate(State state) {
        switch (state) {
            case IDLE:
                if (TouchSensor::A_wasTapped()) {
                    alwaysOn = !alwaysOn;
                }
                break;
            case SLEEP:
                if (TouchSensor::B_wasTapped()) {
                    changeState(IDLE);
                }
                break;
            default:
                break;
        }
    }

    void stateExit(State state) {
        switch (state) {
            case IDLE:
                break;
            default:
                break;
        }
    }

    void changeState(State nextState) {
        stateExit(state);
        state = nextState;
        stateEnter(state);
    }
}

void Behavior::initialize() {
    state = LOGO;
    stateEnter(state);
}

void Behavior::update() {
    stateUpdate(state);
}