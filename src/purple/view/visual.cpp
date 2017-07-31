#include "visual.hpp"
#include "exceptions.hpp"

#include <SDL_image.h>

#include <cmath>

Sprite::Sprite(const std::string& filePath)
    : _texture(nullptr, SDL_DestroyTexture)
{
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    checkImgCall("IMG_Load", surface);



}

Sprite::Sprite(std::shared_ptr<Image> texture, int width, int height)
    : _texture(texture)
    , _width(width)
    , _height(height)
{ }

void Sprite::render(Canvas& canvas, const ScreenPoint& position)
{
    canvas.draw(
        *_texture,
        {0, 0, _width, _height},
        {position.x - _width / 2, position.y - _height / 2, _width, _height});
}

Animation::Animation(
        std::shared_ptr<Image> texture,
        int frameWidth,
        int frameHeight,
        int frameCount,
        double fps)
    : _texture(texture)
    , _frameWidth(frameWidth)
    , _frameHeight(frameHeight)
    , _frameCount(frameCount)
    , _secondsPerFrame(1.0 / fps)
    , _playTime(0)
{ }

void Animation::render(Canvas& canvas, const ScreenPoint& position)
{
    int frame = static_cast<int>(_playTime / _secondsPerFrame);
    int textureX = frame * _frameWidth;
    canvas.draw(
        *_texture,
        {textureX, 0, _frameWidth, _frameHeight},
        {position.x - _frameWidth / 2, position.y - _frameHeight / 2,
            _frameWidth, _frameHeight});
}

void Animation::update(double deltaSec)
{
    double animationTime = _secondsPerFrame * _frameCount;
    _playTime = std::fmod(_playTime + deltaSec, animationTime);
}

Text::Text(std::shared_ptr<Font> font, const std::string& text)
{
     TTF_RenderText_Shaded(font.get(), text.c_str(), {0, 0, 0, 255}, {255, 255, 255, 255});
}