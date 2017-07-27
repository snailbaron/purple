#pragma once

#include "renderer.hpp"
#include "geometry.hpp"

class Visual {
public:
    virtual void render(Renderer& canvas, const ScreenPoint& position) = 0;
    virtual void update(double deltaSec) {};
};

class Sprite : public Visual {
public:
    Sprite(std::shared_ptr<Texture> texture, int width, int height);

    void render(Renderer& canvas, const ScreenPoint& position) override;

private:
    std::shared_ptr<Texture> _texture;
    int _width;
    int _height;
};

class Animation : public Visual {
public:
    Animation(
        std::shared_ptr<Texture> texture,
        int frameWidth,
        int frameHeight,
        int frameCount,
        double fps);
    
    void render(Renderer& canvas, const ScreenPoint& position) override;
    void update(double deltaSec) override;

private:
    std::shared_ptr<Texture> _texture;
    int _frameWidth;
    int _frameHeight;
    int _frameCount;
    double _secondsPerFrame;
    double _playTime = 0;
};