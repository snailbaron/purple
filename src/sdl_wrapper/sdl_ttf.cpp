#include <sdl_wrapper/sdl/surface.hpp>
#include <sdl_wrapper/sdl/utils.hpp>
#include <sdl_wrapper/sdl_ttf.hpp>

#include "errors.hpp"

using namespace sdl;

namespace ttf {

Font::Font(TTF_Font* ptr)
    : _font(ptr, TTF_CloseFont)
{ }

Size Font::sizeUtf8(const std::string& text)
{
    Size size;
    TTF_SizeUTF8(_font.get(), text.c_str(), &size.w, &size.h);
    return size;
}

std::shared_ptr<Surface> Font::renderUtf8Solid(
    const std::string& text, const SDL_Color& fg)
{
    SDL_Surface* surface = TTF_RenderUTF8_Solid(_font.get(), text.c_str(), fg);
    if (!surface) {
        throw SdlTtfError("TTF_RenderUTF8_Solid");
    }

    return std::make_shared<Surface>(surface);
}

std::shared_ptr<Surface> Font::renderUtf8Shaded(
    const std::string& text, const SDL_Color& fg, const SDL_Color& bg)
{
    SDL_Surface* surface = TTF_RenderUTF8_Shaded(
        _font.get(), text.c_str(), fg, bg);
    if (!surface) {
        throw SdlTtfError("TTF_RenderUTF8_Shaded");
    }

    return std::make_shared<Surface>(surface);
}

std::shared_ptr<Surface> Font::renderUtf8Blended(
    const std::string& text, const SDL_Color& fg)
{
    SDL_Surface* surface = TTF_RenderUTF8_Blended(
        _font.get(), text.c_str(), fg);
    if (!surface) {
        throw SdlTtfError("TTF_RenderUTF8_Blended");
    }

    return std::make_shared<Surface>(surface);
}

std::shared_ptr<Font> openFont(const std::string& file, int ptsize)
{
    TTF_Font* font = TTF_OpenFont(file.c_str(), ptsize);
    if (!font) {
        throw SdlTtfError("TTF_OpenFont");
    }

    return std::make_shared<Font>(font);
}

} // namespace ttf
