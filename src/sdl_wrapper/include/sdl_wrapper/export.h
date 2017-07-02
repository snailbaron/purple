#pragma once

#ifdef _WIN32
#   ifdef SDL_WRAPPER_BUILD
#       define EXPORT __declspec(dllexport)
#   else
#       define EXPORT __declspec(dllimport)
#   endif
#else
#   define EXPORT
#endif