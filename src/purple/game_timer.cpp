#include "game_timer.hpp"
#include <sdl_wrapper.hpp>

GameTimer::GameTimer()
    : _prevTimeSec(sdl::getTicks() / 1000.0)
{ }

bool GameTimer::advance(double deltaSec)
{
    double currentTimeSec = sdl::getTicks() / 1000.0;
    if (currentTimeSec - _prevTimeSec >= deltaSec) {
        _prevTimeSec += deltaSec;
        return true;
    }
    return false;
}

double GameTimer::delay() const
{
    double currentTimeSec = sdl::getTicks() / 1000.0;
    return currentTimeSec - _prevTimeSec;
}
