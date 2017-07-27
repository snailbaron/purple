#include "game_timer.hpp"

#include <SDL.h>

GameTimer::GameTimer()
    : _prevTimeSec(SDL_GetTicks() / 1000.0)
{ }

bool GameTimer::advance(double deltaSec)
{
    double currentTimeSec = SDL_GetTicks() / 1000.0;
    if (currentTimeSec - _prevTimeSec >= deltaSec) {
        _prevTimeSec += deltaSec;
        return true;
    }
    return false;
}

double GameTimer::delay() const
{
    double currentTimeSec = SDL_GetTicks() / 1000.0;
    return currentTimeSec - _prevTimeSec;
}
