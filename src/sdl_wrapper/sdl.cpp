#include "singleton.hpp"
#include "errors.hpp"
#include "export.hpp"
#include "video_impl.hpp"

#include <sdl_wrapper/sdl.hpp>
#include <SDL.h>

#include <stdexcept>
#include <sstream>

namespace sdl {

namespace {

/**
 * SDL system state
 */
class Sdl {
public:
    Sdl(Uint32 sdlFlags = SDL_INIT_VIDEO | SDL_INIT_AUDIO,
        Uint32 imgFlags = IMG_INIT_PNG | IMG_INIT_JPG);
    ~Sdl();

    // Initialization and shutdown
    void initSubSystem(Uint32 flags);
    void quitSubSystem(Uint32 flags);

    // Video
    std::shared_ptr<Window> createWindow(
        const std::string& title, int x, int y, int w, int h, Uint32 flags);
};

Sdl::Sdl(Uint32 sdlFlags, Uint32 imgFlags)
{
    if (SDL_Init(sdlFlags) != 0) {
        throw SdlError("SDL_Init");
    }
    //if (IMG_Init(imgFlags) != 0) {
    //    throw SdlImageError("IMG_Init");
    //}
    if (TTF_Init() != 0) {
        throw SdlTtfError("TTF_Init");
    }
}

Sdl::~Sdl()
{
    TTF_Quit();
    //IMG_Quit();
    SDL_Quit();
}

void Sdl::initSubSystem(Uint32 flags)
{
    if (SDL_InitSubSystem(flags) != 0) {
        throw SdlError("SDL_InitSubSystem");
    }
}

void Sdl::quitSubSystem(Uint32 flags)
{
    SDL_QuitSubSystem(flags);
}

Sdl& sdlInstance()
{
    return Singleton<Sdl>::instance();
}

} // namespace

//
// Initialization and shutdown
//

EXPORT void init()
{
    Singleton<Sdl>::initialize();
}

EXPORT void initSubSystem(Uint32 flags)
{
    sdlInstance().initSubSystem(flags);
}

EXPORT void quit()
{
    Singleton<Sdl>::destroy();
}

EXPORT void quitSubSystem(Uint32 flags)
{
    sdlInstance().quitSubSystem(flags);
}

EXPORT Uint32 wasInit(Uint32 flags)
{
    return SDL_WasInit(flags);
}

//
// video
//

std::shared_ptr<Window> Sdl::createWindow(
    const std::string& title, int x, int y, int w, int h, Uint32 flags)
{
    return std::shared_ptr<Window>(new WindowImpl(title, x, y, w, h, flags));
}

//
// Exported functions
//

EXPORT std::shared_ptr<Window> createWindow(
    const std::string& title, int x, int y, int w, int h, Uint32 flags)
{
    return sdlInstance().createWindow(title, x, y, w, h, flags);
}

} // namespace sdl
