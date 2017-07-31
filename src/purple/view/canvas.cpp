#include "canvas.hpp"
#include "exceptions.hpp"

#include <purple/config.hpp>

#include <utility>


RendererData::RendererData()
    : _window(nullptr)
    , _canvas(nullptr)
{
    _window = SDL_CreateWindow(
        config::window::Title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        config::window::Width,
        config::window::Height,
        SDL_WINDOW_RESIZABLE);
    checkSdlCall("SDL_CreateWindow", _window);

    _canvas = SDL_CreateRenderer(
        _window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    checkSdlCall("SDL_CreateRenderer", _canvas);
}

RendererData::RendererData(RendererData&& other)
    : _window(other._window)
    , _canvas(other._canvas)
{ }

RendererData& RendererData::operator=(RendererData&& other)
{
    std::swap(_window, other._window);
    std::swap(_canvas, other._canvas);
    return *this;
}

RendererData::~RendererData()
{
    SDL_DestroyRenderer(_canvas);
    SDL_DestroyWindow(_window);
}

void Canvas::clear(const Color& color)
{
    int result;

    result = SDL_SetRenderDrawColor(
        _data.renderer(), color.r, color.g, color.b, color.a);
    checkSdlCall("SDL_SetRenderDrawColor", result == 0);

    result = SDL_RenderClear(_data.renderer());
    checkSdlCall("SDL_RenderClear", result == 0);
}

void Canvas::present()
{
    SDL_RenderPresent(_data.renderer());
}

Image Canvas::loadTexture(const std::string& filePath) const
{
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    checkImgCall("IMG_Load", surface);
    int width = surface->w;
    int height = surface->h;

    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(_data.renderer(), surface);
    checkSdlCall("SDL_CreateTextureFromSurface", texture);

    SDL_FreeSurface(surface);

    return Image(texture, width, height);
}

void Canvas::draw(const Image& image, const ScreenPosition& position)
{
    // Texture is not really modified
    SDL_Texture* sdlTexture = const_cast<SDL_Texture*>(image.raw());

    int windowWidth, windowHeight;
    SDL_GetWindowSize(_data.window, &windowWidth, &windowHeight);

    SDL_Rect srcRect {0, 0, image.width(), image.height()};

    int rawPositionX =
        position.point.x.fraction * windowWidth + position.point.x.pixels;
    int rawPositionY =
        position.point.y.fraction * windowHeight + position.point.y.pixels;

    SDL_Point rotationCenter {0, 0};

    if (position.anchor == ScreenPosition::Anchor::Center) {
        rawPositionX -= image.width() / 2;
        rawPositionY -= image.height() / 2;
        rotationCenter.x = image.width() / 2;
        rotationCenter.y = image.height() / 2;
    }

    SDL_Rect dstRect {
        rawPositionX,
        rawPositionY,
        image.width(),
        image.height()
    };

    int result = SDL_RenderCopyEx(
        _data.renderer(),
        sdlTexture,
        &srcRect,
        &dstRect,
        position.angle,
        &rotationCenter,
        SDL_FLIP_NONE);
    checkSdlCall("SDL_RenderCopyEx", result == 0);
}
