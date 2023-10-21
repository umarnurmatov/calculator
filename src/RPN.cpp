#include "RPN.hpp"
#include <iostream>
#include <stack>
#include <cmath>

void shuntingYard(const std::vector<Token> &expr, std::vector<Token> &outQueue)
{
    std::stack<Token> stack;
    for(const auto& token : expr)
    {
        switch(token.getType())
        {
        case Token::INT_LITERAL:
            outQueue.push_back(token);
            break;
        case Token::FLOAT_LITERAL:
            outQueue.push_back(token);
            break;
        case Token::OPERATOR:
            if(!stack.empty())
            {
                while((stack.top().getPrecendance() > token.getPrecendance())
                        || (stack.top().getPrecendance() == token.getPrecendance() && token.getAsc() == Token::LEFT))
                {
                    outQueue.push_back(stack.top());
                    stack.pop();
                    if(stack.empty()) 
                        break;
                }
            }
            stack.push(token);
            break;
        case Token::O_PARANTHESIS:
            stack.push(token);
            break;
        case Token::C_PARANTHESIS:
            if(stack.empty()) 
                break;
            while (stack.top().getType() != Token::O_PARANTHESIS)
            {
                outQueue.push_back(stack.top());
                stack.pop();
                if (stack.empty())
                    throw CustomException("Non-balanced on paranthesis expression!");
            }
            stack.pop();
            break;
        }
    }
    while(!stack.empty())
    {
        if(stack.top().getType() == Token::O_PARANTHESIS)
            throw CustomException("Non-balanced on paranthesis expression!");
        else
        {
            outQueue.push_back(stack.top());
            stack.pop();
        }
    } 
}

double countRPN(const std::vector<Token> &expr)
{
    std::stack<double> stack;
    for(auto& token : expr)
    {
        switch(token.getType())
        {
        case Token::INT_LITERAL:
            stack.push(std::stof(token.getStr()));
            break;
        case Token::FLOAT_LITERAL:
            stack.push(std::stof(token.getStr()));
            break;
        case Token::OPERATOR:
        {
            const std::string &str = token.getStr();
            double a,b,res;
            switch(token.getAsc())
            {
            case Token::LEFT:
            {
                b = stack.top();
                stack.pop();
                a = stack.top();
                stack.pop();
                if      (str == "+") res = a + b;
                else if (str == "-") res = a - b;
                else if (str == "*") res = a * b;
                else if (str == "/") res = a / b;
                else if (str == "^") res = std::pow(a,b);
                else    throw CustomException("Unknown operator!");
                break;
            }
            case Token::RIGHT:
            {
                a = stack.top();
                stack.pop();
                if   (str == "-") res = -a;
                else throw CustomException("Unknown operator!");
                break;
            }
            }
            stack.push(res);
            break;
        }
        case Token::O_PARANTHESIS:
            throw CustomException("Paranthesis in RPN!");
            break;
        case Token::C_PARANTHESIS:
            throw CustomException("Paranthesis in RPN!");
            break;
        } 
    }
    return stack.top();
}
