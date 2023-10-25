#pragma once
#include <string>

class Token
{
public:
    // Тип
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

    // Ассоциативность
    enum OperatorAssociativity
    {
        NONE,  // токен - не оператор
        RIGHT, // правоассоциативный
        LEFT   // левоассоциативный
    };

    Token(std::string token, Type type, OperatorAssociativity asc = NONE);

    // Приоритет
    int getPrecendance() const;

    const Type& getType() const  { return type; }
    const OperatorAssociativity& getAsc() const { return opAsc; }
    const std::string& getStr() const { return str; }

private:
    Type type;
    OperatorAssociativity opAsc;
    std::string str;
};
