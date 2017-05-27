#include "errors.hpp"

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <sstream>

SdlError::SdlError(const std::string& function)
{
    std::ostringstream ss;
    ss << "SDL error in " << function << ": " << SDL_GetError();
    _message = ss.str();
}

const char* SdlError::what() const
{
    return _message.c_str();
}
