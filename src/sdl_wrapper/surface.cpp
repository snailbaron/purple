#include <sdl_wrapper/sdl/surface.hpp>
#include <sdl_wrapper/sdl/utils.hpp>

namespace sdl {

Surface::Surface(SDL_Surface* surface)
    : _surface(surface, SDL_FreeSurface)
{ }

int Surface::w() const
{
    return _surface->w;
}

int Surface::h() const
{
    return _surface->h;
}

Size Surface::size() const
{
    return { _surface->w, _surface->h };
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

} // namespace sdl