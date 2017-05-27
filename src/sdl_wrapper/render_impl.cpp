#include "render_impl.hpp"

namespace sdl {

TextureImpl::TextureImpl(SDL_Texture* ptr = nullptr)
    : _texture(ptr, SDL_DestroyTexture)
{ }

RendererImpl::RendererImpl(SDL_Renderer* renderer, std::shared_ptr<Window> window)
    : _window(window)
    , _renderer(renderer, SDL_DestroyRenderer)
{ }

//Texture RendererImpl::createTextureFromSurface(const Surface& surface) const
//{
//    return Texture(
//        SDL_CreateTextureFromSurface(
//            _renderer.get(), surface._surface));
//}

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

//void RendererImpl::copy(
//    const Texture& texture,
//    const SDL_Rect* srcrect,
//    const SDL_Rect* dstrect)
//{
//    SDL_RenderCopy(_renderer.get(), texture._texture.get(), srcrect, dstrect);
//}

} // namespace sdl