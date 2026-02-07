#include "timer.hpp"

void Timer::start() {
    paused = false;
    last = millis();
}

void Timer::reset() {
    done = false;
    paused = true;
    elapsed = 0;
    last = millis();
}

void Timer::pause() {
    paused = true;
}

void Timer::resume() {
    start();
}

void Timer::update() {
    if (done || paused) return;

    uint32_t now = millis();
    elapsed += now - last;
    last = now;

    if (elapsed > duration) done = true;
}

bool Timer::isDone() {
    return done;
}

void Timer::setDuration(uint32_t duration) {
    reset();
    this->duration = duration;
}