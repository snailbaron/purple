#pragma once

#include <sdl/render.hpp>
#include <sdl/surface.hpp>
#include <sdl/video.hpp>
#include <memory>

namespace sdl {

class RendererImpl : public sdl::Renderer {
public:
    RendererImpl(SDL_Renderer* renderer, std::shared_ptr<Window> window);

    //Texture createTextureFromSurface(const Surface& surface) const;

    void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) override;
    void clear() override;
    void present() override;

    void fillRect(const SDL_Rect& rect) override;
    //void copy(
    //    const Texture& texture,
    //    const SDL_Rect* srcrect,
    //    const SDL_Rect* dstrect);

private:
    std::shared_ptr<Window> _window;
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> _renderer;
};


class TextureImpl : public Texture {
public:
    TextureImpl(SDL_Texture* ptr);

    std::shared_ptr<SDL_Texture> _texture;
};

} // namespace sdl