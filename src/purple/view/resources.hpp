#pragma once

#include "canvas.hpp"
#include <sdl_wrapper.hpp>
#include <map>
#include <string>
#include <memory>

class Resources {
public:
    void loadBitmaps();
    void convertBitmapsToTextures(const Canvas& canvas);

    std::shared_ptr<sdl::Texture> texture(const std::string& key) const;

private:
    std::map<std::string, std::shared_ptr<sdl::Surface>> _bitmaps;
    std::map<std::string, std::shared_ptr<sdl::Texture>> _textures;
};