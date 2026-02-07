#ifndef TIMER_HPP
#define TIMER_HPP

#include <Arduino.h>

class Timer {
    private:
    uint32_t duration = 0;
    uint32_t elapsed = 0;
    uint32_t last = 0;

    bool paused = true;
    bool done = false;

    public:
    Timer(uint32_t duration) : duration(duration) {}

    void start();
    void reset();
    void pause();
    void resume();
    void update();
    bool isDone();

    void setDuration(uint32_t duration);
};

#endif // TIMER_HPP