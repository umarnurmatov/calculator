#pragma once
#include <string>

class SyntaxError
{
public:
    SyntaxError(std::string msg)
    {
        _msg = "Syntax Error: " + msg;
    }
    std::string what() { return _msg; }

private:
    std::string _msg;
};

