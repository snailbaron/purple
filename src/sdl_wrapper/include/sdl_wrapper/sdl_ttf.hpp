#pragma once

#include <sdl_wrapper/export.h>

#include <memory>
#include <string>
#include <utility>

#include <SDL_ttf.h>

namespace sdl {

struct Size;
class Surface;

} // namespace sdl

namespace ttf {

class Font {
public:
    Font(TTF_Font* font);

    sdl::Size sizeUtf8(const std::string& text);

    std::shared_ptr<sdl::Surface> renderUtf8Solid(
        const std::string& text, const SDL_Color& fg);
    std::shared_ptr<sdl::Surface> renderUtf8Shaded(
        const std::string& text, const SDL_Color& fg, const SDL_Color& bg);
    std::shared_ptr<sdl::Surface> renderUtf8Blended(
        const std::string& text, const SDL_Color& fg);

private:
    std::unique_ptr<TTF_Font, void(*)(TTF_Font*)> _font;
};

} // namespace ttf
