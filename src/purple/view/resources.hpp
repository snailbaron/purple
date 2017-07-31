#pragma once

#include "canvas.hpp"
#include "visual.hpp"

#include <SDL.h>

#include <map>
#include <string>
#include <memory>

class Image {
public:
    Image(const std::string& filePath);

    int width() const { return _sdlSurface->w; }
    int height() const { return _sdlSurface->h; }

    SDL_Surface* raw() const { return _sdlSurface.get(); }

private:
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> _sdlSurface;
};

class Resource {};

class GraphicsResource : public Resource {
public:
    virtual std::unique_ptr<Visual> createGraphics() const = 0;
};

class BitmapResource : public GraphicsResource {
public:
    BitmapResource(std::shared_ptr<Image> texture, int width, int height)
        : _texture(texture), _width(width), _height(height) {}

    std::unique_ptr<Visual> createGraphics() const override;

private:
    std::shared_ptr<Image> _texture;
    int _width;
    int _height;
};

class AnimationResource : public GraphicsResource {
public:
    AnimationResource(
            std::shared_ptr<Image> texture,
            int frameWidth,
            int frameHeight,
            int frameCount)
        : _texture(texture)
        , _frameWidth(frameWidth)
        , _frameHeight(frameHeight)
        , _frameCount(frameCount)
    { }

    std::unique_ptr<Visual> createGraphics() const override;

private:
    std::shared_ptr<Image> _texture;
    int _frameWidth;
    int _frameHeight;
    int _frameCount;
};

class ResourceStorage {
public:
    void loadGraphics(const Canvas& canvas, const std::string& location);
    void loadTestLevel();

    std::shared_ptr<GraphicsResource> graphics(const std::string& key) const;

private:
    std::shared_ptr<BitmapResource> loadBitmapResource(
        const Canvas& canvas, const std::string& path);
    std::shared_ptr<AnimationResource> loadAnimationResource(
        const Canvas& canvas, const std::string& path);

    std::map<std::string, std::shared_ptr<GraphicsResource>> _graphicalResources;
};