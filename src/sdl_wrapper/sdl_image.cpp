#include "errors.hpp"
#include "surface_impl.hpp"
#include <sdl_wrapper/sdl_image.hpp>

namespace img {

EXPORT std::shared_ptr<sdl::Surface> load(const std::string& file)
{
    SDL_Surface* surface = IMG_Load(file.c_str());
    if (!surface) {
        throw SdlImageError("IMG_Load");
    }

    return std::shared_ptr<sdl::Surface>(
        new sdl::SurfaceImpl(surface));
}

} // namespace img
