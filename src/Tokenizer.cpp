#include "Tokenizer.hpp"
#include <iostream>
#include <format>

void TokenizerFSM::tokenize(std::string &expr, std::vector<Token> &tokens)
{
    bool isDigit, isLetter, isOp, isParanth, isPoint, isSep, isLParanth, isRParanth;
    std::string buffer;
    Token::Type bufferTokenType = Token::INT_LITERAL;
    for(auto& s : expr)
    {
        isDigit = std::isdigit(s);
        isLetter = std::isalpha(s);
        isLParanth = s == '(';
        isRParanth = s == ')';
        isParanth = isLParanth || isRParanth;
        isPoint = s == '.';
        isSep = s == ',';
        isOp = ops.find(s) != ops.npos;

        if(!(isDigit || isLetter || isParanth || isPoint || isSep || isOp))
            throw CustomException(std::format("Syntax Error: Unknown symbol: {}", s));

        // смена состояния
        switch(state)
        {
        case S0:
            if (isOp || isParanth)
                state = S1;
            else if (isDigit)
                state = S2;
            else if (isLetter)
                state = S4;
            else if (isPoint || isSep)
                throw CustomException(std::format("Syntax Error: Unexpected symbol: {}", s));
            break;
        case S1:
            if (isDigit)
                state = S2;
            else if (isLetter)
                state = S4;
            else if (isPoint || isSep)
                throw CustomException(std::format("Syntax Error: Unexpected symbol: {}", s));
            break;
        case S2:
            bufferTokenType = Token::INT_LITERAL;
            if (isPoint)
                state = S3;
            else if (isParanth || isOp || isSep)
                state = S5;
            else if (isLetter)
                throw CustomException(std::format("Syntax Error: Unexpected symbol: {}", s));
            break;
        case S3:
            bufferTokenType = Token::FLOAT_LITERAL;
            if (isParanth || isOp || isSep)
                state = S5;
            else if (isPoint)
                throw CustomException(std::format("Syntax Error: Unexpected symbol: {}", s));
            break;
        case S4:
            bufferTokenType = Token::FUNCTION;
            if(isLParanth)
                state = S5;
            else if(isDigit || isOp || isRParanth || isSep)
                throw CustomException(std::format("Syntax Error: Unexpected symbol: {}", s));
            break;
        case S5:
            if (isParanth || isOp)
                state = S1;
            else if (isDigit)
                state = S2;
            else if (isPoint || isSep)
                throw CustomException(std::format("Syntax Error: Unexpected symbol: {}", s));
            break;
        default:
            break;
        }

        auto tokenize_Op_Paranth_Sep = [&]() 
        {
            if(isOp)
            {
                // обработка unary negation
                if(tokens[tokens.size()-1].getType() == Token::L_PARANTHESIS || tokens.size() == 0)
                    tokens.push_back({std::string{s}, Token::OPERATOR, Token::RIGHT});
                else
                    tokens.push_back({std::string{s}, Token::OPERATOR, Token::LEFT});
            }
            else if(isParanth)
            {
                if(isLParanth)
                    tokens.push_back({std::string{s}, Token::L_PARANTHESIS, Token::LEFT});
                else
                    tokens.push_back({std::string{s}, Token::R_PARANTHESIS});
            }
            else if(isSep)
            {
                tokens.push_back({std::string{s}, Token::SEPARATOR});
            }
        };

        // действия
        switch(state)
        {
        case S0:
            break;
        case S1:
            tokenize_Op_Paranth_Sep();
            break;
        case S2:
            buffer.push_back(s);
            break;
        case S3:
            buffer.push_back(s);
            break;
        case S4:
            buffer.push_back(s);
            break;
        case S5:
            tokens.push_back({buffer, bufferTokenType});
            buffer.clear();
            tokenize_Op_Paranth_Sep();
            break;
        }   
    }
    if(!buffer.empty())
        tokens.push_back({buffer, bufferTokenType});
}

