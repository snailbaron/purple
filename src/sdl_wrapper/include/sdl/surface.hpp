#pragma once

#include <SDL.h>
#include <string>

namespace sdl {
    class Surface;
}

namespace img {
    sdl::Surface load(const std::string& file);
}

namespace ttf {
    class Font;
}

namespace sdl {

class Surface {
    friend class Renderer;
    friend class ttf::Font;
    friend Surface img::load(const std::string& file);

public:
    Surface();
    Surface(const Surface& other);
    ~Surface();

    Surface& operator=(const Surface& other);
    Surface& operator=(Surface&& other);
    explicit operator bool() const;

    const SDL_PixelFormat& format() const;
    int w() const;
    int h() const;
    int pitch() const;
    void* pixels();
    void* userdata();
    const SDL_Rect& clipRect() const;
    int& refcount();

    void fillRect(const SDL_Rect& rect, Uint32 color);

private:
    Surface(SDL_Surface* ptr);

    SDL_Surface* _surface;
};

} // namespace sdl