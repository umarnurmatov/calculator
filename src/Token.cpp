#include "Token.hpp"
#include <map>
#include "SyntaxError.hpp"

Token::Token(std::string token, Type type, OperatorAssociativity asc)
: type{type}
, str{token}
{
    // если токен - оператор, но ассоциативность не задана - ошибка
    if(type == OPERATOR && asc == NONE)
        throw SyntaxError("Associativity required!");

    // если токен - НЕ оператор, но ассоциативность задана - ошибка
    else if(type != OPERATOR && asc != NONE)
        throw SyntaxError("Non-operator token can't have an associativity!");

    opAsc = asc;
}

int Token::getPrecendance() const
{
    static std::map<std::string, int> op_leftassociative = 
    {
        {"+", 2},
        {"-", 2},
        {"/", 3},
        {"*", 3},
        {"^", 5}
    };


    static std::map<std::string, int> op_rightassociative = 
    {
        {"-", 4} // унарное отрицание
    };

    switch(opAsc)
    {
    case LEFT:
        if(op_leftassociative.contains(str)) return op_leftassociative[str];
        else throw SyntaxError("Unknown Operator!");
        break;
    case RIGHT:
        if(op_rightassociative.contains(str)) return op_rightassociative[str];
        else throw SyntaxError("Unknown Operator!");
        break;
    case NONE:
        throw SyntaxError("Token is not an operator, impossible!");
        break;
    }
}
