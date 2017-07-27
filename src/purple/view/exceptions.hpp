#pragma once

#include <purple/exceptions.hpp>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <string>
#include <utility>
#include <exception>

template <const char* (*Getter)()>
class BasicSdlError : public std::exception {
public:
    BasicSdlError(const std::string& function)
    {
        _message = function + Getter();
    }

    const char* what() const override
    {
        return _message.c_str();
    }

private:
    std::string _message;
};

using SdlError = BasicSdlError<SDL_GetError>;
using ImgError = BasicSdlError<IMG_GetError>;
using TtfError = BasicSdlError<TTF_GetError>;

inline void checkSdlCall(const std::string& function, bool condition)
{
    checkOrThrow<SdlError>(condition, function);
}

inline void checkImgCall(const std::string& function, bool condition)
{
    checkOrThrow<ImgError>(condition, function);
}

inline void checkTtfCall(const std::string& function, bool condition)
{
    checkOrThrow<TtfError>(condition, function);
}