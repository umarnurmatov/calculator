#pragma once
#include <string>

class Token
{
public:
    enum Type
    {
        OPERATOR,      // унарный/бинарный оператор
        C_PARANTHESIS, // закрывающая скобка
        O_PARANTHESIS, // открывающая скобка
        INT_LITERAL,   // целое число
        FLOAT_LITERAL  // число с плавающей точкой (double)
    };

    enum OperatorAssociativity
    {
        NONE,  // токен - не оператор / не открыващая скобка
        RIGHT,
        LEFT
    };

    Token(std::string token, Type type, OperatorAssociativity asc = NONE);
    
    int getPrecendance() const;

    const Type& getType() const  { return type; }
    const OperatorAssociativity& getAsc() const { return opAsc; }
    const std::string& getStr() const { return str; }

private:
    Type type;
    OperatorAssociativity opAsc;
    std::string str;
};
