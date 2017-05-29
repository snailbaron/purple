#pragma once

#include <sdl_wrapper.hpp>
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

class Canvas {
public:
    Canvas();

    void clear(const Color& color);
    void present();

private:
    std::shared_ptr<sdl::Renderer> _renderer;
};