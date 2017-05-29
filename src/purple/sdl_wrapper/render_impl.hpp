#pragma once

#include <sdl_wrapper/sdl/render.hpp>
#include <sdl_wrapper/sdl/surface.hpp>
#include <sdl_wrapper/sdl/video.hpp>
#include <memory>

namespace sdl {

class RendererImpl : public sdl::Renderer {
public:
    RendererImpl(SDL_Renderer* renderer, std::shared_ptr<Window> window);

    std::shared_ptr<Texture> createTextureFromSurface(
        std::shared_ptr<Surface> surface) const;

    void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) override;
    void clear() override;
    void present() override;

    void fillRect(const SDL_Rect& rect) override;
    void copy(
        std::shared_ptr<Texture> texture,
        const SDL_Rect& srcrect,
        const SDL_Rect& dstrect) override;

private:
    std::shared_ptr<Window> _window;
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> _renderer;
};


class TextureImpl : public Texture {
public:
    TextureImpl(SDL_Texture* ptr);

    SDL_Texture* raw() { return _texture.get(); }

private:
    std::shared_ptr<SDL_Texture> _texture;
};

} // namespace sdl