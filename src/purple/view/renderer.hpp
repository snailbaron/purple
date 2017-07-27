#pragma once

#include <SDL.h>

#include <memory>
#include <cstdint>

struct Color {
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        : r(r), g(g), b(b), a(a) {}

    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

class Texture {
public:
    Texture(SDL_Texture* rawTexture)
        : _sdlTexture(rawTexture, SDL_DestroyTexture)
    { }

    SDL_Texture* raw() { return _sdlTexture.get(); }
    const SDL_Texture* raw() const { return _sdlTexture.get(); }

private:
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> _sdlTexture;
};

class RendererData {
public:
    RendererData();

    RendererData(const RendererData&) = delete;
    RendererData(RendererData&& other);

    RendererData& operator=(const RendererData&) = delete;
    RendererData& operator=(RendererData&& other);

    ~RendererData();

    // Many SDL functions take non-constant SDL_Window and SDL_Renderer
    // pointers, event if they don't modify the structures. Mark these accessors
    // const for simplicity of use.

    SDL_Window* window() const { return _window; }
    SDL_Renderer* renderer() const { return _renderer; }

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
};

class Renderer {
public:
    struct Size {
        int width;
        int height;
    };

    class Rect;

    SDL_Renderer* raw() const { return _data.renderer(); }

    Size size() const;

    void clear(const Color& color);
    void present();

    void drawTexture(const Texture& texture, const Rect& src, const Rect& dst);
    
private:
    RendererData _data;
};

class Renderer::Rect {
public:
    Rect(int x, int y, int width, int height)
        : _sdlRect {x, y, width, height}
    { }

    SDL_Rect& sdl() { return _sdlRect; }
    const SDL_Rect& sdl() const { return _sdlRect; }

    SDL_Rect* sdlPtr() { return &_sdlRect; }
    const SDL_Rect* sdlPtr() const { return &_sdlRect; }

private:
    SDL_Rect _sdlRect;
};
