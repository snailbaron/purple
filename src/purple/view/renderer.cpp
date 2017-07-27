#include "renderer.hpp"
#include "exceptions.hpp"

#include <purple/config.hpp>

#include <utility>

RendererData::RendererData()
    : _window(nullptr)
    , _renderer(nullptr)
{
    _window = SDL_CreateWindow(
        config::window::Title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        config::window::Width,
        config::window::Height,
        SDL_WINDOW_RESIZABLE);
    checkSdlCall("SDL_CreateWindow", _window);

    _renderer = SDL_CreateRenderer(
        _window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    checkSdlCall("SDL_CreateRenderer", _renderer);
}

RendererData::RendererData(RendererData&& other)
    : _window(other._window)
    , _renderer(other._renderer)
{ }

RendererData& RendererData::operator=(RendererData&& other)
{
    std::swap(_window, other._window);
    std::swap(_renderer, other._renderer);
    return *this;
}

RendererData::~RendererData()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

Renderer::Size Renderer::size() const
{
    // Window is not really modified
    SDL_Window* window = const_cast<SDL_Window*>(_data.window());

    Size size;
    SDL_GetWindowSize(window, &size.width, &size.height);
    return size;
}

void Renderer::clear(const Color& color)
{
    int result;

    result = SDL_SetRenderDrawColor(
        _data.renderer(), color.r, color.g, color.b, color.a);
    checkSdlCall("SDL_SetRenderDrawColor", result == 0);

    result = SDL_RenderClear(_data.renderer());
    checkSdlCall("SDL_RenderClear", result == 0);
}

void Renderer::present()
{
    SDL_RenderPresent(_data.renderer());
}

void Renderer::drawTexture(
    const Texture& texture, const Rect& src, const Rect& dst)
{
    // Texture is not really modified
    SDL_Texture* sdlTexture = const_cast<SDL_Texture*>(texture.raw());

    int result = SDL_RenderCopy(
        _data.renderer(), sdlTexture, src.sdlPtr(), dst.sdlPtr());
    checkSdlCall("SDL_RenderCopy", result == 0);
}
