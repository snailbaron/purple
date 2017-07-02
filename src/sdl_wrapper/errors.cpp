#include "errors.hpp"

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <sstream>

BaseSdlError::BaseSdlError(
    const std::string& library,
    const char* (*getError)(),
    const std::string& function)
{
    std::ostringstream ss;
    ss << library << " error in " << function << ": " << getError();
    _message = ss.str();
}

const char* BaseSdlError::what() const
{
    return _message.c_str();
}
