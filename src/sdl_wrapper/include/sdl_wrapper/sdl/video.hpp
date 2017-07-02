#pragma once

#include <sdl_wrapper/sdl/utils.hpp>
#include <sdl_wrapper/export.h>

#include <memory>
#include <tuple>
#include <cstdint>
#include <string>
#include <utility>

namespace sdl {

class EXPORT Window : public std::enable_shared_from_this<Window> {
public:
    Window(
        const std::string& title, int x, int y, int w, int h, uint32_t flags);

    std::shared_ptr<Renderer> createRenderer(
        int index, uint32_t flags);

    Size size() const;

private:
    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> _window;
};

} // namespace sdl
