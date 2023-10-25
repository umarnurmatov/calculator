#include <map>
#include <stdexcept>
#include "Token.hpp"
#include "Error.hpp"

Token::Token(std::string token, Type type, OperatorAssociativity asc)
: type{type}
, str{token}
{
    // если токен - оператор, но ассоциативность не задана - ошибка
    if(type == OPERATOR && asc == NONE)
        throw std::logic_error("Associativity required!");

    // если токен - НЕ оператор, но ассоциативность задана - ошибка
    else if(type != OPERATOR && asc != NONE)
        throw std::logic_error("Non-operator token can't have an associativity!");

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
        else throw Error("Unknown Operator!", Error::Syntax);
        break;
    case RIGHT:
        if(op_rightassociative.contains(str)) return op_rightassociative[str];
        else throw Error("Unknown Operator!", Error::Syntax);
        break;
    case NONE:
        throw std::logic_error("Token is not an operator, impossible!");
        break;
    }
}
