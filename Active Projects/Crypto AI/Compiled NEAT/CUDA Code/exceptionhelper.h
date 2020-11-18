#pragma once

#include <string>
#include <exception>

class InvalidOperationException : public std::exception
{
private:
    std::string msg;

public:
    InvalidOperationException(const std::string& message = "") : msg(message)
    {
    }

    const char * what() const noexcept
    {
        return msg.c_str();
    }
};
