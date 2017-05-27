#pragma once

#include <sdl_wrapper/sdl/surface.hpp>
#include <memory>

namespace sdl {

class SurfaceImpl : public Surface {
public:
    SurfaceImpl(SDL_Surface* surface);

    SDL_Surface* raw() { return _surface.get(); }

    const SDL_PixelFormat& format() const override;
    int w() const override;
    int h() const override;
    Size size() const override;

    int pitch() const override;
    void* pixels() override;
    void* userdata() override;
    const SDL_Rect& clipRect() const override;
    int& refcount() override;

private:
    std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> _surface;
};

} // namespace sdl