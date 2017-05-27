#pragma once

#include <export.hpp>
#include <sdl_wrapper/sdl/surface.hpp>
#include <SDL.h>
#include <memory>

namespace sdl {

class Texture {};

class EXPORT Renderer {
public:
    virtual std::shared_ptr<Texture> createTextureFromSurface(
        std::shared_ptr<Surface> surface) const = 0;

    virtual void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) = 0;
    virtual void clear() = 0;
    virtual void present() = 0;

    virtual void fillRect(const SDL_Rect& rect) = 0;
    virtual void copy(
        std::shared_ptr<Texture> texture,
        const SDL_Rect& srcrect,
        const SDL_Rect& dstrect) = 0;
};

} // namespace sdl