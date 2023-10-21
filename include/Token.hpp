#pragma once
#include <string>
#include <map>

struct Token
{
    enum Type
    {
        OPERATOR,     // унарный/бинарный оператор
        PARANTHESIS,  // скобка
        INT_LITERAL,  // целое число
        FLOAT_LITERAL // число с плавающей точкой (double)
    };

    Type type;
    std::string tokenStr;
    
    Token(std::string token, Type t)
    : type{t}
    , tokenStr{token}
    {}

    // -1, если нет приоритета
    int getPrecendance()
    {
        static std::map<std::string, int> p = 
        {
            {"+", 2},
            {"-", 2},
            {"/", 3},
            {"*", 3},
            {"%", 4},
            {"^", 5},
            {"(", -1}
        };
        if(p.contains(tokenStr))
            return p[tokenStr];
        return -1;
    }
};
