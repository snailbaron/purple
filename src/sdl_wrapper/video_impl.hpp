#pragma once

#include <sdl_wrapper/sdl/video.hpp>

namespace sdl {

class WindowImpl : public Window, public std::enable_shared_from_this<WindowImpl> {
public:
    WindowImpl(const WindowImpl&) = delete;
    WindowImpl& operator=(const WindowImpl&) = delete;

    WindowImpl(const std::string& title, int x, int y, int w, int h, Uint32 flags);
    ~WindowImpl();

    std::shared_ptr<Renderer> createRenderer(int index, Uint32 flags);

private:
    SDL_Window* _window = nullptr;
};

} // namespace sdl