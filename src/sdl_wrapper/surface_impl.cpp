#include "surface_impl.hpp"

namespace sdl {

SurfaceImpl::SurfaceImpl(SDL_Surface* surface)
    : _surface(surface, SDL_FreeSurface)
{ }

const SDL_PixelFormat& SurfaceImpl::format() const
{
    return *_surface->format;
}

int SurfaceImpl::w() const
{
    return _surface->w;
}

int SurfaceImpl::h() const
{
    return _surface->h;
}

Size SurfaceImpl::size() const
{
    return { _surface->w, _surface->h };
}

int SurfaceImpl::pitch() const
{
    return _surface->pitch;
}

void* SurfaceImpl::pixels()
{
    return _surface->pixels;
}

void* SurfaceImpl::userdata()
{
    return _surface->userdata;
}

const SDL_Rect& SurfaceImpl::clipRect() const
{
    return _surface->clip_rect;
}

int& SurfaceImpl::refcount()
{
    return _surface->refcount;
}

} // namespace sdl