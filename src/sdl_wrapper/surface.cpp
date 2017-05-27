#include <sdl/surface.hpp>

namespace sdl {

Surface::Surface()
    : Surface(nullptr)
{ }

Surface::Surface(SDL_Surface* ptr)
    : _surface(ptr)
{ }

Surface::Surface(const Surface& other)
    : _surface(nullptr)
{
    if (other._surface) {
        _surface = SDL_ConvertSurface(
            other._surface, other._surface->format, 0);
    }
}

Surface::~Surface()
{
    if (_surface) {
        SDL_FreeSurface(_surface);
    }
}

Surface& Surface::operator=(const Surface& other)
{
    if (_surface) {
        SDL_FreeSurface(_surface);
    }

    if (other._surface) {
        _surface = SDL_ConvertSurface(
            other._surface, other._surface->format, 0);
    }
    else {
        _surface = nullptr;
    }

    return *this;
}

Surface& Surface::operator=(Surface&& other)
{
    std::swap(_surface, other._surface);
    return *this;
}

Surface::operator bool() const
{
    return !!_surface;
}

const SDL_PixelFormat& Surface::format() const
{
    return *_surface->format;
}

int Surface::w() const
{
    return _surface->w;
}

int Surface::h() const
{
    return _surface->h;
}

int Surface::pitch() const
{
    return _surface->pitch;
}

void* Surface::pixels()
{
    return _surface->pixels;
}

void* Surface::userdata()
{
    return _surface->userdata;
}

const SDL_Rect& Surface::clipRect() const
{
    return _surface->clip_rect;
}

int& Surface::refcount()
{
    return _surface->refcount;
}

void Surface::fillRect(const SDL_Rect& rect, Uint32 color)
{
    SDL_FillRect(_surface, &rect, color);
}

} // namespace sdl