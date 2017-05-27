#pragma once

#include <export.hpp>
#include <sdl/surface.hpp>
#include <SDL.h>
#include <memory>

namespace sdl {

class Texture {};

class EXPORT Renderer {
public:
    //Texture createTextureFromSurface(const Surface& surface) const;

    virtual void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) = 0;
    virtual void clear() = 0;
    virtual void present() = 0;

    virtual void fillRect(const SDL_Rect& rect) = 0;
    //void copy(
    //    const Texture& texture,
    //    const SDL_Rect* srcrect,
    //    const SDL_Rect* dstrect);
};

} // namespace sdl