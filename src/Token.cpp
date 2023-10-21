#include "Token.hpp"
#include <map>
#include "CustomException.hpp"

Token::Token(std::string token, Type type, OperatorAssociativity asc)
: type{type}
, str{token}
{
    if((type == OPERATOR || type == O_PARANTHESIS) && asc == NONE)
        throw CustomException("Associativity required!");
    else if(type != OPERATOR && type != O_PARANTHESIS && asc != NONE)
        throw CustomException("Non-operator/non-opening-paranthesis token can't have an associativity!");

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
        {"%", 4},
        {"-", 5},
        {"^", 7},
        {"(", -1}
    };


    static std::map<std::string, int> op_rightassociative = 
    {
        {"-", 6} // unary negation
    };

    switch(opAsc)
    {
    case LEFT:
        if(op_leftassociative.contains(str)) return op_leftassociative[str];
        else throw CustomException("Unknown Operator!");
        break;
    case RIGHT:
        if(op_rightassociative.contains(str)) return op_rightassociative[str];
        else throw CustomException("Unknown Operator!");
        break;
    case NONE:
        throw CustomException("Token is not a operator, impossible!");
        break;
    }
}