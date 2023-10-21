#include "Tokenizer.hpp"
#include <iostream>
#include <format>

void TokenizerFSM::tokenize(std::string &expr, std::vector<Token> &tokens)
{
    bool isDigit, isOp, isParanth, isPoint;
    std::string buffer;
    Token::Type bufferLiteralType = Token::INT_LITERAL;
    for(auto& s : expr)
    {
        isDigit = std::isdigit(s);
        isParanth = (s == '(') || (s == ')');
        isPoint = s == '.';
        isOp = ops.find(s) != ops.npos; 

        if(!isDigit && !isParanth && !isPoint && !isOp)
            throw CustomException(std::format("Unknown symbol: {}", s));

        // смена состояния
        switch(state)
        {
        case S0:
            if(isDigit)
                state = S2;
            else if(isPoint)
                throw CustomException("Unexpected symbol: .");
            else if(isOp || isParanth)
                state = S1;
            break;
        case S1:
            if(isDigit)
                state = S2;
            else if(isPoint)
                throw CustomException("Unexpected symbol: .");
        case S2:
            bufferLiteralType = Token::INT_LITERAL;
            if(isParanth | isOp)
                state = S4;
            else if(isPoint)
                state = S3;
            break;
        case S3:
            bufferLiteralType = Token::FLOAT_LITERAL;
            if(isParanth | isOp)
                state = S4;
            else if(isPoint)
                throw CustomException("Unexpected symbol: .");
            break;
        case S4:
            if(isParanth | isOp)
                state = S1;
            else if(isDigit)
                state = S2;
            else if(isPoint)
                throw CustomException("Unexpected symbol: .");
            break;
        default:
            throw CustomException("Unrecognized state");
        }

        // действия
        switch(state)
        {
        case S0:
            break;
        case S1:
            tokens.push_back({std::string{s}, isParanth ? Token::PARANTHESIS : Token::OPERATOR});
            break;
        case S2:
            buffer.push_back(s);
            break;
        case S3:
            buffer.push_back(s);
            break;
        case S4:
            tokens.push_back({buffer, bufferLiteralType});
            buffer.clear();
            tokens.push_back({std::string{s}, isParanth ? Token::PARANTHESIS : Token::OPERATOR});
            break;
        }   
    }
    if(!buffer.empty())
        tokens.push_back({buffer, bufferLiteralType});
}
