#pragma once

#include "sdl/render.hpp"
#include "sdl/surface.hpp"
#include "sdl/video.hpp"

#include <SDL.h>

namespace sdl {

void init();
void initSubSystem(Uint32 flags);
void quit();
void quitSubSystem(Uint32 flags);
Uint32 wasInit(Uint32 flags);

std::shared_ptr<Window> createWindow(
    const std::string& title, int x, int y, int w, int h, Uint32 flags);

} // namespace sdl