#pragma once

#include <sdl_wrapper/sdl/utils.hpp>
#include <sdl_wrapper/export.h>

#include <SDL.h>

#include <memory>
#include <string>

namespace sdl {

class EXPORT Surface {
public:
    Surface(SDL_Surface* surface);

    int w() const;
    int h() const;
    Size size() const;
    int pitch() const;
    void* pixels();
    void* userdata();
    const SDL_Rect& clipRect() const;
    int& refcount();

    SDL_Surface* raw() { return _surface.get(); }

private:
    std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> _surface;
};

} // namespace sdl