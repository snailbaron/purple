#include "ttf.hpp"

namespace ttf {

Font::Font()
    : _font(nullptr)
{ }

Font::Font(TTF_Font* ptr)
    : _font(ptr, TTF_CloseFont)
{ }

Font::Size Font::sizeUtf8(const std::string& text)
{
    Size size;
    TTF_SizeUTF8(_font.get(), text.c_str(), &size.w, &size.h);
    return size;
}

sdl::Surface Font::renderUtf8Solid(const std::string& text, const SDL_Color& fg)
{
    return sdl::Surface(
        TTF_RenderUTF8_Solid(_font.get(), text.c_str(), fg));
}

sdl::Surface Font::renderUtf8Shaded(
    const std::string& text, const SDL_Color& fg, const SDL_Color& bg)
{
    return sdl::Surface(
        TTF_RenderUTF8_Shaded(_font.get(), text.c_str(), fg, bg));
}

sdl::Surface Font::renderUtf8Blended(const std::string& text, const SDL_Color& fg)
{
    sdl::Surface surface(
        TTF_RenderUTF8_Blended(_font.get(), text.c_str(), fg));

    return surface;
}

Font openFont(const std::string& file, int ptsize)
{
    return Font(TTF_OpenFont(file.c_str(), ptsize));
}

} // namespace ttf
