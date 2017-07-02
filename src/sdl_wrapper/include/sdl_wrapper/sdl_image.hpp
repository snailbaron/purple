#pragma once

#include <sdl_wrapper/export.h>

#include <string>
#include <memory>

namespace sdl {

class Surface;

} // namespace sdl

namespace img {

EXPORT std::shared_ptr<sdl::Surface> load(const std::string& file);

} // namespace img
