#pragma once

#include <sdl/render.hpp>
#include <SDL.h>
#include <memory>

namespace sdl {

class EXPORT Window {
public:
    virtual std::shared_ptr<Renderer> createRenderer(
        int index, Uint32 flags) = 0;
};

} // namespace sdl
