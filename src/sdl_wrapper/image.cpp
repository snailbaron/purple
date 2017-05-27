#include <image.hpp>
#include <SDL_image.h>

namespace img {

sdl::Surface load(const std::string& file)
{
    return sdl::Surface(IMG_Load(file.c_str()));
}

} // namespace img
