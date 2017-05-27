#include "render_impl.hpp"
#include "surface_impl.hpp"
#include "errors.hpp"

namespace sdl {

TextureImpl::TextureImpl(SDL_Texture* ptr = nullptr)
    : _texture(ptr, SDL_DestroyTexture)
{ }

RendererImpl::RendererImpl(SDL_Renderer* renderer, std::shared_ptr<Window> window)
    : _window(window)
    , _renderer(renderer, SDL_DestroyRenderer)
{ }

std::shared_ptr<Texture> RendererImpl::createTextureFromSurface(
    std::shared_ptr<Surface> surface) const
{
    std::shared_ptr<SurfaceImpl> surfaceImpl =
        std::static_pointer_cast<SurfaceImpl, Surface>(surface);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(
        _renderer.get(), surfaceImpl->raw());
    if (!texture) {
        throw SdlError("SDL_CreateTextureFromSurface");
    }

    return std::shared_ptr<Texture>(new TextureImpl(texture));
}

void RendererImpl::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(_renderer.get(), r, g, b, a);
}

void RendererImpl::clear()
{
    SDL_RenderClear(_renderer.get());
}

void RendererImpl::present()
{
    SDL_RenderPresent(_renderer.get());
}

void RendererImpl::fillRect(const SDL_Rect& rect)
{
    SDL_RenderFillRect(_renderer.get(), &rect);
}

void RendererImpl::copy(
    std::shared_ptr<Texture> texture,
    const SDL_Rect& srcrect,
    const SDL_Rect& dstrect)
{
    auto textureImpl = std::static_pointer_cast<TextureImpl, Texture>(texture);
    if (SDL_RenderCopy(
            _renderer.get(), textureImpl->raw(), &srcrect, &dstrect) != 0) {
        throw SdlError("SDL_RenderCopy");
    }
}

} // namespace sdl