#pragma once

#include <purple/utils/basic_geometry.hpp>
#include <purple/core/geometry.hpp>

// There is currently no difference between a point and an offset/size. We may
// try to change it in the future.
using ScreenPoint = Vector<int>;
using ScreenSize = Vector<int>;
using ScreenOffset = Vector<int>;

ScreenOffset worldToScreenOffset(const WorldOffset& worldOffset);
