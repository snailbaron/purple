#pragma once

template <class Exception, class... Args>
void checkOrThrow(bool condition, Args&&... args)
{
    if (!condition) {
        throw Exception(std::forward<Args>(args)...);
    }
}
