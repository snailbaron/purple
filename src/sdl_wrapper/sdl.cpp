#include <sdl_wrapper/sdl.hpp>
#include <sdl_wrapper/sdl/video.hpp>

#include "errors.hpp"

#include <SDL.h>

#include <stdexcept>
#include <sstream>

namespace sdl {

//
// Initialization and shutdown
//

EXPORT void init(
    uint32_t sdlFlags = SDL_INIT_VIDEO | SDL_INIT_AUDIO,
    uint32_t imgFlags = IMG_INIT_PNG | IMG_INIT_JPG)
{
    if (SDL_Init(sdlFlags) != 0) {
        throw SdlError("SDL_Init");
    }
    if (IMG_Init(imgFlags) != imgFlags) {
        throw SdlImageError("IMG_Init");
    }
    if (TTF_Init() != 0) {
        throw SdlTtfError("TTF_Init");
    }
}

EXPORT void initSubSystem(Uint32 flags)
{
    if (SDL_InitSubSystem(flags) != 0) {
        throw SdlError("SDL_InitSubSystem");
    }
}

EXPORT void quit()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

EXPORT void quitSubSystem(uint32_t flags)
{
    SDL_QuitSubSystem(flags);
}

EXPORT Uint32 wasInit(uint32_t flags)
{
    return SDL_WasInit(flags);
}

//
// video
//

EXPORT std::shared_ptr<Window> createWindow(
    const std::string& title, int x, int y, int w, int h, uint32_t flags)
{
    return std::make_shared<Window>(title, x, y, w, h, flags);
}

//
// timer
//

EXPORT uint32_t getTicks()
{
    return SDL_GetTicks();
}

} // namespace sdl
