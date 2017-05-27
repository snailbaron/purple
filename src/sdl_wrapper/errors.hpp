#pragma once

#include <exception>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class BaseSdlError : public std::exception {
public:
    BaseSdlError(
        const std::string& library,
        const char* (*getError)(),
        const std::string& function);

    const char* what() const override;

private:
    std::string _message;
};

class SdlError : public BaseSdlError {
public:
    SdlError(const std::string& function)
        : BaseSdlError("SDL", SDL_GetError, function) {}
};

class SdlImageError : public BaseSdlError {
public:
    SdlImageError(const std::string& function)
        : BaseSdlError("SDL_image", IMG_GetError, function) {}
};

class SdlTtfError : public BaseSdlError {
public:
    SdlTtfError(const std::string& function)
        : BaseSdlError("SDL_ttf", TTF_GetError, function) {}
};
