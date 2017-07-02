#include <sdl_wrapper/sdl/render.hpp>
#include <sdl_wrapper/sdl/surface.hpp>

#include "errors.hpp"

namespace sdl {

class Window;

Texture::Texture(SDL_Texture* ptr)
    : _texture(ptr, SDL_DestroyTexture)
{ }

Renderer::Renderer(
        SDL_Renderer* renderer, std::shared_ptr<Window> window)
    : _renderer(renderer, SDL_DestroyRenderer)
    , _window(window)
{ }

std::shared_ptr<Texture> Renderer::createTextureFromSurface(
    std::shared_ptr<Surface> surface) const
{
    auto surfaceImpl = std::static_pointer_cast<Surface>(surface);

    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(_renderer.get(), surfaceImpl->raw());
    if (!texture) {
        throw SdlError("SDL_CreateTextureFromSurface");
    }

    return std::make_shared<Texture>(texture);
}

void Renderer::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(_renderer.get(), r, g, b, a);
}

void Renderer::clear()
{
    SDL_RenderClear(_renderer.get());
}

void Renderer::present()
{
    SDL_RenderPresent(_renderer.get());
}

void Renderer::fillRect(const SDL_Rect& rect)
{
    SDL_RenderFillRect(_renderer.get(), &rect);
}

void Renderer::copy(
    std::shared_ptr<Texture> texture,
    const SDL_Rect& srcrect,
    const SDL_Rect& dstrect)
{
    if (SDL_RenderCopy(
            _renderer.get(), texture->raw(), &srcrect, &dstrect) != 0) {
        throw SdlError("SDL_RenderCopy");
    }
}

} // namespace sdl