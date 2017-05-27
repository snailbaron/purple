#pragma once

#include <export.hpp>
#include "sdl/render.hpp"
#include "sdl/surface.hpp"
#include "sdl/video.hpp"

namespace sdl {

EXPORT void init(Uint32 flags);
EXPORT void initSubSystem(Uint32 flags);
EXPORT void quit();
EXPORT void quitSubSystem(Uint32 flags);
EXPORT Uint32 wasInit(Uint32 flags);

EXPORT std::shared_ptr<Window> createWindow(
    const std::string& title, int x, int y, int w, int h, Uint32 flags);


} // namespace sdl