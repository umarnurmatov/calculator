#pragma once
#include <string>

class CustomException
{
public:
    CustomException(std::string msg)
    {
        _msg = "CustomError: " + msg;
    }
    std::string what() { return _msg; }

private:
    std::string _msg;
};

