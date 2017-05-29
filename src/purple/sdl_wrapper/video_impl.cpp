#include "errors.hpp"
#include "video_impl.hpp"
#include "render_impl.hpp"

namespace sdl {

WindowImpl::WindowImpl(
        const std::string& title, int x, int y, int w, int h, Uint32 flags)
{
    _window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
    if (!_window) {
        throw SdlError("SDL_CreateWindow");
    }
}

WindowImpl::~WindowImpl()
{
    if (_window) {
        SDL_DestroyWindow(_window);
    }
}

std::shared_ptr<Renderer> WindowImpl::createRenderer(int index, Uint32 flags)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(_window, index, flags);
    if (!renderer) {
        throw SdlError("SDL_CreateRenderer");
    }

    return std::shared_ptr<Renderer>(
        new RendererImpl(renderer, shared_from_this()));
}

} // namespace sdl