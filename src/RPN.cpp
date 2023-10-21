#include "RPN.hpp"
#include <stack>
#include <cmath>

void shuntingYard(std::vector<Token> &expr, std::vector<Token> &outQueue)
{
    std::stack<Token> stack;
    for(auto& token : expr)
    {
        switch(token.type)
        {
        case Token::INT_LITERAL:
            outQueue.push_back(token);
            break;
        case Token::FLOAT_LITERAL:
            outQueue.push_back(token);
            break;
        case Token::OPERATOR:
            while(!stack.empty() && stack.top().getPrecendance() > token.getPrecendance())
            {
                outQueue.push_back(stack.top());
                stack.pop();
            }
            stack.push(token);
            break;
        case Token::PARANTHESIS:
            if(token.tokenStr == "(")
                stack.push(token);
            else
            {
                while(stack.top().tokenStr != "(")
                {
                    outQueue.push_back(stack.top());
                    stack.pop();
                    if(stack.empty())
                        throw CustomException("Non-balanced on paranthesis expression!");
                }
                stack.pop();
            }
            break;
        }
    }
    while(!stack.empty())
    {
        if(stack.top().tokenStr == "(")
            throw CustomException("Non-balanced on paranthesis expression!");
        else
        {
            outQueue.push_back(stack.top());
            stack.pop();
        }
    } 
}

// Обратная польская запись ОБЯЗАНА быть валидной
double countRPN(std::vector<Token> &expr)
{
    std::stack<double> stack;
    for(auto& token : expr)
    {
        switch(token.type)
        {
        case Token::INT_LITERAL:
            stack.push(std::stof(token.tokenStr));
            break;
        case Token::FLOAT_LITERAL:
            stack.push(std::stof(token.tokenStr));
            break;
        case Token::OPERATOR:
            std::string &str = token.tokenStr;
            double b = stack.top();
            stack.pop();
            double a = stack.top();
            stack.pop();
            double res;
            if      (str == "+") res = a + b;
            else if (str == "-") res = a - b;
            else if (str == "*") res = a * b;
            else if (str == "/") res = a / b;
            else if (str == "^") res = std::pow(a,b);
            else    throw CustomException("Unknown operator!");
            stack.push(res);
            break;
        } 
    }
    return stack.top();
}
