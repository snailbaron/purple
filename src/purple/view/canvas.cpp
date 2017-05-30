#include "canvas.hpp"

namespace {

const char WINDOW_TITLE[] = "Purple";
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

}

Canvas::Canvas()
{
    auto window = sdl::createWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE);
    _renderer = window->createRenderer(
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

void Canvas::drawTexture(std::shared_ptr<sdl::Texture> texture)
{
    // This bullshit is just to finally see something apart from the gray
    // screen. Please remove ASAP.
    _renderer->copy(texture, {0, 0, 64, 64}, {10, 10, 64, 64});
}