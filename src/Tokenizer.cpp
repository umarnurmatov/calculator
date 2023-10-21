#include "Tokenizer.hpp"
#include <iostream>
#include <format>

void TokenizerFSM::tokenize(std::string &expr, std::vector<Token> &tokens)
{
    bool isDigit, isOp, isParanth, isPoint, isOParanth, isCParanth;
    std::string buffer;
    Token::Type bufferLiteralType = Token::INT_LITERAL;
    for(auto& s : expr)
    {
        isDigit = std::isdigit(s);
        isOParanth = s == '(';
        isCParanth = s == ')';
        isParanth = isOParanth || isCParanth;
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
            else if (isOp || isParanth)
                state = S1;
            break;
        case S1:
            if(isDigit)
                state = S2;
            else if(isPoint)
                throw CustomException("Unexpected symbol: .");
            break;
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
                throw CustomException ("Unexpected symbol: .");
            break;
        default:
            throw CustomException("Unrecognized state");
            break;
        }

        auto addOperatorOrParanthesis = [&]() 
        {
            if(isOp)
            {
                // обработка unary negation
                if(tokens[tokens.size()-1].getType() == Token::O_PARANTHESIS || tokens.size() == 0)
                    tokens.push_back({std::string{s}, Token::OPERATOR, Token::RIGHT});
                else
                    tokens.push_back({std::string{s}, Token::OPERATOR, Token::LEFT});
            }
            else if(isParanth)
            {
                if(isOParanth)
                    tokens.push_back({std::string{s}, Token::O_PARANTHESIS, Token::LEFT});
                else
                    tokens.push_back({std::string{s}, Token::C_PARANTHESIS});
            }
        };

        // действия
        switch(state)
        {
        case S0:
            break;
        case S1:
            addOperatorOrParanthesis();
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
            addOperatorOrParanthesis();
            break;
        }   
    }
    if(!buffer.empty())
        tokens.push_back({buffer, bufferLiteralType});
}

