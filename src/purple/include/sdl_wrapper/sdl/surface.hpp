#pragma once

#include <sdl_wrapper/sdl/utils.hpp>
#include <SDL.h>
#include <string>

namespace sdl {

class Surface {
public:
    virtual const SDL_PixelFormat& format() const = 0;
    virtual int w() const = 0;
    virtual int h() const = 0;
    virtual Size size() const = 0;
    virtual int pitch() const = 0;
    virtual void* pixels() = 0;
    virtual void* userdata() = 0;
    virtual const SDL_Rect& clipRect() const = 0;
    virtual int& refcount() = 0;
};

} // namespace sdl