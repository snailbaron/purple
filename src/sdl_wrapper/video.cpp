#include <sdl_wrapper/sdl/render.hpp>
#include <sdl_wrapper/sdl/video.hpp>
#include <sdl_wrapper/sdl/utils.hpp>

#include "errors.hpp"

namespace sdl {

Window::Window(
        const std::string& title, int x, int y, int w, int h, uint32_t flags)
    : _window(
        SDL_CreateWindow(title.c_str(), x, y, w, h, flags),
        SDL_DestroyWindow)
{
    if (!_window) {
        throw SdlError("SDL_CreateWindow");
    }
}

Size Window::size() const
{
    Size result;
    SDL_GetWindowSize(_window.get(), &result.w, &result.h);
    return result;
}

std::shared_ptr<Renderer> Window::createRenderer(int index, uint32_t flags)
{
    SDL_Renderer* renderer =
        SDL_CreateRenderer(_window.get(), index, flags);
    if (!renderer) {
        throw SdlError("SDL_CreateRenderer");
    }

    return std::make_shared<Renderer>(renderer, shared_from_this());
}

} // namespace sdl