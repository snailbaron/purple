#pragma once

#include <sdl_wrapper/sdl_ttf.hpp>
#include <memory>

namespace ttf {

class FontImpl : public Font {
public:
    FontImpl(TTF_Font* font);

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

std::shared_ptr<Font> openFont(const std::string& file, int ptsize);

} // namespace ttf
