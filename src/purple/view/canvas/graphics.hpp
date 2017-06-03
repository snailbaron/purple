#pragma once

#include <sdl_wrapper.hpp>
#include "canvas.hpp"

class Graphics {
public:
    virtual void render(Canvas& canvas, const ScreenPoint& position) = 0;
    virtual void update(double deltaSec) {};
};

class Sprite : public Graphics {
public:
    Sprite(std::shared_ptr<sdl::Texture> texture, int width, int height);

    void render(Canvas& canvas, const ScreenPoint& position) override;

private:
    std::shared_ptr<sdl::Texture> _texture;
    int _width;
    int _height;
};

class Animation : public Graphics {
public:
    Animation(
        std::shared_ptr<sdl::Texture> texture,
        int frameWidth,
        int frameHeight,
        int frameCount,
        double fps);
    
    void render(Canvas& canvas, const ScreenPoint& position) override;
    void update(double deltaSec) override;

private:
    std::shared_ptr<sdl::Texture> _texture;
    int _frameWidth;
    int _frameHeight;
    int _frameCount;
    double _secondsPerFrame;
    double _playTime = 0;
};