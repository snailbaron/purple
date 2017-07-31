#pragma once

#include "geometry.hpp"

#include <SDL.h>

#include <memory>
#include <cstdint>
#include <string>

struct Color {
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        : r(r), g(g), b(b), a(a) {}

    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
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
    SDL_Renderer* renderer() const { return _canvas; }

private:
    SDL_Window* _window;
    SDL_Renderer* _canvas;
};

class Image {
public:
    Image(SDL_Texture* texture, int width, int height)
        : _texture(texture, SDL_DestroyTexture)
        , _width(width)
        , _height(height)
    { }

    SDL_Texture* raw() const { return _texture.get(); }

    int width() const { return _width; }
    int height() const { return _height; }

private:
    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> _texture;
    int _width;
    int _height;
};

class Font {
    Font(TTF_Font* font)
        : _font(font, TTF_CloseFont)
    { }

    TTF_Font* raw() const { return _font.get(); }

private:
    std::unique_ptr<TTF_Font, void(*)(TTF_Font*)> _font;
};

class Canvas {
public:
    SDL_Renderer* raw() const { return _data.renderer(); }

    void clear(const Color& color);
    void present();

    void draw(const Image& texture, const ScreenPosition& position);

private:
    Image loadTexture(const std::string& filePath) const;

    RendererData _data;
};
