#include "resources.hpp"
#include "exceptions.hpp"

#include <SDL_image.h>

#include <filesystem>
#include <stdexcept>

namespace fs = std::experimental::filesystem;

namespace {

std::shared_ptr<Texture> makeTexture(const Image& image, const Renderer& renderer)
{
    SDL_Texture* rawTexture =
        SDL_CreateTextureFromSurface(renderer.raw(), image.raw());
    checkSdlCall("SDL_CreateTextureFromSurface", rawTexture);

    return std::make_shared<Texture>(rawTexture);
}

} // namespace

Image::Image(const std::string& filePath)
    : _sdlSurface(nullptr, SDL_FreeSurface)
{
    SDL_Surface* rawSurface = IMG_Load(filePath.c_str());
    checkImgCall("IMG_Load", rawSurface);

    _sdlSurface.reset(rawSurface);
}

std::unique_ptr<Visual> BitmapResource::createGraphics() const
{
    return std::make_unique<Sprite>(_texture, _width, _height);
}

std::unique_ptr<Visual> AnimationResource::createGraphics() const
{
    return std::make_unique<Animation>(
        _texture, _frameWidth, _frameHeight, _frameCount, 3);
}

std::shared_ptr<GraphicsResource> ResourceStorage::graphics(
    const std::string& key) const
{
    auto i = _graphicalResources.find(key);
    if (i == _graphicalResources.end()) {
        throw std::runtime_error(
            "ResourceStorage: no resource having key '" + key + "'");
    }

    return i->second;
}

void ResourceStorage::loadGraphics(const Renderer& canvas, const std::string& location)
{
    fs::path basePath = location;

    _graphicalResources.clear();

    fs::path bitmapsDir = basePath / "bitmaps";
    if (!fs::is_directory(bitmapsDir)) {
        throw std::runtime_error(
            "ResourceStorage: location '" + location +
            "' does not look like a resource storage");
    }

    for (const auto& entry : fs::directory_iterator(bitmapsDir)) {
        std::string key = "bitmaps/" + entry.path().filename().string();
        _graphicalResources[key] = loadBitmapResource(
            canvas, entry.path().string());
    }

    fs::path animationsDir = basePath / "animations";
    for (const auto& entry : fs::directory_iterator(animationsDir)) {
        std::string key = "animations/" + entry.path().filename().string();
        _graphicalResources[key] = loadAnimationResource(
            canvas, entry.path().string());
    }
}

// Placeholder from loading a real level from a file. Create TileLevel object
// from code.
void ResourceStorage::loadTestLevel()
{

}

std::shared_ptr<BitmapResource> ResourceStorage::loadBitmapResource(
    const Renderer& renderer, const std::string& path)
{
    Image image(path);
    auto texture = makeTexture(image, renderer);
    return std::make_shared<BitmapResource>(
        texture, image.width(), image.height());
}

std::shared_ptr<AnimationResource> ResourceStorage::loadAnimationResource(
    const Renderer& renderer, const std::string& path)
{
    Image image(path);
    auto texture = makeTexture(image, renderer);

    // Gross hack: assume that the animation is stored frame-by-frame
    // horizontally in a flat graphics file; assume that each frame is a seuqre.
    // No error checking.
    int frameCount = image.width() / image.height();

    return std::make_shared<AnimationResource>(
        texture, image.height(), image.height(), frameCount);
}

