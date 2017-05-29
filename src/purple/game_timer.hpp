#pragma once

#include <sdl_wrapper.hpp>

/**
 * A timer to perform actions in regular intervals. Stores the last moment when
 * the action was performed.
 *
 * Using a single operation you can:
 * - Check if it is time to perform the action again
 * - If it is, update the stored value with current time
 */
class GameTimer {
public:
    /**
     * Initialize timer with current time (as if the action was first performed
     * in the moment of construction).
     */
    GameTimer();

    /**
     * Try to advance currently stored value by <deltaSec> seconds forward. If
     * such moment is not in the future (already happened), increase the stored
     * value by <deltaSec> and return true. Otherwise, return false.
     */
    bool advance(double deltaSec);

private:
    Uint32 _prevTime;
};