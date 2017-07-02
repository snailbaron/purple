#pragma once

#include <sdl_wrapper/export.h>

#include <SDL.h>

#include <memory>
#include <cstdint>

namespace sdl {

class Surface;
class Window;

class EXPORT Texture {
public:
    explicit Texture(SDL_Texture* ptr = nullptr);

    SDL_Texture* raw() { return _texture.get(); }

private:
    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> _texture;
};

class EXPORT Renderer {
public:
    Renderer(SDL_Renderer* renderer, std::shared_ptr<Window> window);

    std::shared_ptr<Texture> createTextureFromSurface(
        std::shared_ptr<Surface> surface) const;

    void setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void clear();
    void present();

    void fillRect(const SDL_Rect& rect);
    void copy(
        std::shared_ptr<Texture> texture,
        const SDL_Rect& srcrect,
        const SDL_Rect& dstrect);

    SDL_Renderer* raw() { return _renderer.get(); }

private:
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> _renderer;
    std::shared_ptr<Window> _window;
};


} // namespace sdl