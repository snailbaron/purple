#include "canvas.hpp"

namespace {

const char WINDOW_TITLE[] = "Purple";
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

}

Canvas::Canvas()
{
    _window = sdl::createWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE);
    _renderer = _window->createRenderer(
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

ScreenSize Canvas::size() const
{
    sdl::Size windowSize = _window->size();
    return {windowSize.w, windowSize.h};
}

ScreenPoint Canvas::middle() const
{
    return size() / 2;
}

std::shared_ptr<sdl::Texture> Canvas::createTextureFromSurface(
    std::shared_ptr<sdl::Surface> surface) const
{
    return _renderer->createTextureFromSurface(surface);
}

void Canvas::clear(const Color& color)
{
    _renderer->setDrawColor(color.r, color.g, color.b, color.a);
    _renderer->clear();
}

void Canvas::present()
{
    _renderer->present();
}

void Canvas::drawTexture(
    std::shared_ptr<sdl::Texture> texture,
    const SDL_Rect& src,
    const SDL_Rect& dst)
{
    _renderer->copy(texture, src, dst);
}
