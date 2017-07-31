#pragma once

#include <purple/utils/basic_geometry.hpp>
#include <purple/core/geometry.hpp>

// There is currently no difference between a point and an offset/size. We may
// try to change it in the future.
//using ScreenPoint = Vector<int>;
//using ScreenSize = Vector<int>;
//using ScreenOffset = Vector<int>;
//
//ScreenOffset worldToScreenOffset(const WorldOffset& worldOffset);

struct ScreenCoordinate {
    ScreenCoordinate& operator+=(const ScreenCoordinate& other)
    {
        fraction += other.fraction;
        pixels += other.pixels;
        return *this;
    }

    ScreenCoordinate& operator-=(const ScreenCoordinate& other)
    {
        fraction -= other.fraction;
        pixels -= other.pixels;
        return *this;
    }

    ScreenCoordinate operator-()
    {
        return {-fraction, -pixels};
    }

    float fraction = 0;
    int pixels = 0;
};

ScreenCoordinate operator"" _px(unsigned long long px)
{
    return {0, static_cast<int>(px)};
}

ScreenCoordinate operator"" _frac(long double frac)
{
    return {static_cast<float>(frac), 0};
}

using ScreenPoint = Vector<ScreenCoordinate>;

struct ScreenPosition {
    enum class Anchor {
        TopLeft,
        Center,
    };

    ScreenPosition(
            ScreenPoint point,
            float angle = 0.0f,
            float scale = 1.0f,
            Anchor anchor = Anchor::Center)
        : point(std::move(point))
        , angle(angle)
        , scale(scale)
        , anchor(anchor)
    { }

    ScreenPoint point;
    float angle = 0.0f;
    float scale = 1.0f;
    Anchor anchor = Anchor::Center;
};

