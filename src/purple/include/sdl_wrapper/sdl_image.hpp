#pragma once

#include <sdl_wrapper/sdl/surface.hpp>

#include <SDL_image.h>

#include <string>
#include <memory>

namespace img {

std::shared_ptr<sdl::Surface> load(const std::string& file);

} // namespace img
