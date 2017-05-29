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

void Canvas::clear(const Color& color)
{
    _renderer->setDrawColor(color.r, color.g, color.b, color.a);
    _renderer->clear();
}

void Canvas::present()
{
    _renderer->present();
}