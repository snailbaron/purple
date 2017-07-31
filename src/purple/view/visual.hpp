#pragma once

#include "canvas.hpp"
#include "geometry.hpp"

#include <string>

class Visual {
public:
    virtual void render(Canvas& canvas, const ScreenPoint& position) = 0;
    virtual void update(double deltaSec) {};
};

class Sprite : public Visual {
public:
    void render(Canvas& canvas, const ScreenPoint& position) override;

private:

};

class Animation : public Visual {
public:
    Animation(
        std::shared_ptr<Image> texture,
        int frameWidth,
        int frameHeight,
        int frameCount,
        double fps);

    void render(Canvas& canvas, const ScreenPoint& position) override;
    void update(double deltaSec) override;

private:
    std::shared_ptr<Image> _texture;
    int _frameWidth;
    int _frameHeight;
    int _frameCount;
    double _secondsPerFrame;
    double _playTime = 0;
};

class Text : public Visual {
public:
    Text(std::shared_ptr<Font> font, const std::string& text);

    void render(Canvas& canvas, const ScreenPoint& position) override;
    void update(double deltaSec) override {}

private:
    std::shared_ptr<Font> _font;
    std::string _text;
};