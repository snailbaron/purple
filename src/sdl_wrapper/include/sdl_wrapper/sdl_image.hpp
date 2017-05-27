#pragma once

#include <export.hpp>
#include <sdl_wrapper/sdl/surface.hpp>

#include <SDL_image.h>

#include <string>
#include <memory>

namespace img {

EXPORT std::shared_ptr<sdl::Surface> load(const std::string& file);

} // namespace img
