#include "resources.hpp"
#include <filesystem>

namespace fs = std::experimental::filesystem;

std::shared_ptr<sdl::Texture> Resources::texture(const std::string& key) const
{
    return _textures.at(key);
}

void Resources::loadBitmaps()
{
    _bitmaps.clear();
    for (const auto& entry : fs::directory_iterator("../../assets/bitmaps")) {
        std::string key = entry.path().filename().string();
        auto surface = img::load(entry.path().string());
        _bitmaps[key] = surface;
    }
}

void Resources::convertBitmapsToTextures(const Canvas& canvas)
{
    _textures.clear();
    for (const auto& bitmapPair : _bitmaps) {
        auto texture = canvas.createTextureFromSurface(bitmapPair.second);    
        _textures[bitmapPair.first] = texture;
    }
}