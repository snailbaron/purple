#include <sdl_wrapper/sdl_image.hpp>
#include <sdl_wrapper/sdl/surface.hpp>

#include "errors.hpp"

namespace img {

std::shared_ptr<sdl::Surface> load(const std::string& file)
{
    SDL_Surface* surface = IMG_Load(file.c_str());
    if (!surface) {
        throw SdlImageError("IMG_Load(" + file + ")");
    }

    return std::make_shared<sdl::Surface>(surface);
}

} // namespace img
