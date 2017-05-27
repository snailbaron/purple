#pragma once

#include <sdl/surface.hpp>
#include <string>

namespace img {

sdl::Surface load(const std::string& file);

} // namespace img
