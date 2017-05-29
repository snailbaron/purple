#include "game_timer.hpp"

GameTimer::GameTimer()
    : _prevTime(SDL_GetTicks())
{ }

bool GameTimer::advance(double deltaSec)
{
    Uint32 currentTime = SDL_GetTicks();
    if ((currentTime - _prevTime) / 1000.0 >= deltaSec) {
        _prevTime = currentTime;
        return true;
    }
    return false;
}
