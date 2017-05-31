#include "resources.hpp"
#include "../core/tile_level.h"
#include <filesystem>
#include <stdexcept>

namespace fs = std::experimental::filesystem;

std::shared_ptr<Resource> ResourceStorage::graphics(const std::string& key) const
{
    auto i = _graphicalResources.find(key);
    if (i == _graphicalResources.end()) {
        throw std::runtime_error(
            "ResourceStorage: no resource having key '" + key + "'");
    }

    return i->second;
}

void ResourceStorage::loadGraphics(const Canvas& canvas, const std::string& location)
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
    const Canvas& canvas, const std::string& path)
{
    auto surface = img::load(path);
    auto texture = canvas.createTextureFromSurface(surface);
    return std::make_shared<BitmapResource>(
        texture, surface->w(), surface->h());
}

std::shared_ptr<AnimationResource> ResourceStorage::loadAnimationResource(
    const Canvas& canvas, const std::string& path)
{
    auto surface = img::load(path);
    auto texture = canvas.createTextureFromSurface(surface);

    // Gross hack: assume that the animation is stored frame-by-frame
    // horizontally in a flat graphics file; assume that each frame is a seuqre.
    // No error checking.
    int frameCount = surface->w() / surface->h();

    return std::make_shared<AnimationResource>(
        texture, surface->h(), surface->h(), frameCount);
}

