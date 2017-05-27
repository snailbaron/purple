#pragma once

#include <sdl/surface.hpp>
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>
#include <string>

namespace ttf {

class Font {
    friend Font openFont(const std::string& file, int ptsize);

public:
    struct Size {
        int w;
        int h;
    };

    Font();

    Size sizeUtf8(const std::string& text);

    sdl::Surface renderUtf8Solid(const std::string& text, const SDL_Color& fg);
    sdl::Surface renderUtf8Shaded(
        const std::string& text, const SDL_Color& fg, const SDL_Color& bg);
    sdl::Surface renderUtf8Blended(const std::string& text, const SDL_Color& fg);

private:
    Font(TTF_Font* ptr);

    std::shared_ptr<TTF_Font> _font;
};

Font openFont(const std::string& file, int ptsize);

} // namespace ttf
