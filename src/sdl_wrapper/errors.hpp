#pragma once

#include <exception>
#include <string>

class SdlError : public std::exception {
public:
    SdlError(const std::string& function);

    const char* what() const override;

private:
    std::string _message;
};