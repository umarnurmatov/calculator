#pragma once
#include <string>

class Token
{
public:
    enum Type
    {
        OPERATOR,      // унарный/бинарный оператор
        L_PARANTHESIS, // открывающая скобка
        R_PARANTHESIS, // закрывающая скобка
        INT_LITERAL,   // целое число
        FLOAT_LITERAL, // число с плавающей точкой 
        FUNCTION,      // функция
        SEPARATOR      // разделитель аргументов функции
    };

    enum OperatorAssociativity
    {
        NONE,  // токен - не оператор и не открыващая скобка
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
