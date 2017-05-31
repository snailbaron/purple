#include "geometry.hpp"
#include <cmath>

ScreenOffset worldToScreenOffset(const WorldOffset& worldOffset)
{
    static const double PixelsPerMeter = 32.0;

    return {
        static_cast<int>(std::round(worldOffset.x * PixelsPerMeter)),
        static_cast<int>(std::round(worldOffset.y * PixelsPerMeter))
    };
}