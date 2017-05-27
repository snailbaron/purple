#pragma once

#include <export.hpp>
#include <sdl_wrapper/sdl.hpp>
#include <memory>
#include <string>

#include <SDL_ttf.h>

namespace ttf {

class EXPORT Font {
public:
    virtual sdl::Size sizeUtf8(const std::string& text) = 0;

    virtual std::shared_ptr<sdl::Surface> renderUtf8Solid(
        const std::string& text, const SDL_Color& fg) = 0;
    virtual std::shared_ptr<sdl::Surface> renderUtf8Shaded(
        const std::string& text, const SDL_Color& fg, const SDL_Color& bg) = 0;
    virtual std::shared_ptr<sdl::Surface> renderUtf8Blended(
        const std::string& text, const SDL_Color& fg) = 0;
};

EXPORT std::shared_ptr<Font> openFont(const std::string& file, int ptsize);

} // namespace ttf
