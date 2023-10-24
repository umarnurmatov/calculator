#include "Token.hpp"
#include <map>
#include "SyntaxError.hpp"

Token::Token(std::string token, Type type, OperatorAssociativity asc)
: type{type}
, str{token}
{
    if((type == OPERATOR || type == L_PARANTHESIS) && asc == NONE)
        throw SyntaxError("Associativity required!");
    else if(type != OPERATOR && type != L_PARANTHESIS && asc != NONE)
        throw SyntaxError("Non-operator/non-opening-paranthesis token can't have an associativity!");

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
        else throw SyntaxError("Unknown Operator!");
        break;
    case RIGHT:
        if(op_rightassociative.contains(str)) return op_rightassociative[str];
        else throw SyntaxError("Unknown Operator!");
        break;
    case NONE:
        throw SyntaxError("Token is not a operator, impossible!");
        break;
    }
}
