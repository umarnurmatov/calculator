#include "RPN.hpp"
#include <iostream>
#include <stack>
#include <cmath>
#include <tuple>

void shuntingYard(const std::vector<Token> &expr, std::vector<Token> &outQueue)
{
    std::stack<Token> stack;
    auto fromStackToQueue = [&]() { outQueue.push_back(stack.top()); stack.pop(); };
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
                while(stack.top().getType() == Token::OPERATOR && ((stack.top().getPrecendance() > token.getPrecendance())
                        || (stack.top().getPrecendance() == token.getPrecendance() && token.getAsc() == Token::LEFT)))
                {
                    fromStackToQueue();
                    if(stack.empty()) 
                        break;
                }
            }
            stack.push(token);
            break;
        case Token::L_PARANTHESIS:
            stack.push(token);
            break;
        case Token::R_PARANTHESIS:
            if(stack.empty())
                throw SyntaxError("Non-balanced on paranthesis expression!");
            while (stack.top().getType() != Token::L_PARANTHESIS)
            {
                fromStackToQueue();
                if (stack.empty())
                    throw SyntaxError("Non-balanced on paranthesis expression!");
            }
            stack.pop();
            if(!stack.empty() && stack.top().getType() == Token::FUNCTION)
                fromStackToQueue();
            break;
        case Token::FUNCTION:
            stack.push(token);
            break;
        case Token::SEPARATOR:
            if(stack.empty())
                throw SyntaxError("Paranthesis or separator missed!");
            while(stack.top().getType() != Token::L_PARANTHESIS)
            {
                fromStackToQueue();
                if(stack.empty())
                    throw SyntaxError("Paranthesis or separator missed!");
            }
            break;
        }
    }
    while(!stack.empty())
    {
        if(stack.top().getType() == Token::L_PARANTHESIS)
            throw SyntaxError("Non-balanced on paranthesis expression!");
        else
            fromStackToQueue();
    } 
}

double countRPN(const std::vector<Token> &expr)
{
    std::stack<double> stack;
    auto getOneToken = [&]() { double x = stack.top(); stack.pop(); return x; };
    auto getTwoTokens = [&]()  
        { double x = stack.top(); stack.pop(); double y = stack.top(); stack.pop(); return std::tuple{y,x}; };
    double res;
    for (auto &token : expr)
    {
        const std::string &str = token.getStr();
        switch(token.getType())
        {
        case Token::INT_LITERAL:
            stack.push(std::stof(str));
            break;
        case Token::FLOAT_LITERAL:
            stack.push(std::stof(str));
            break;
        case Token::OPERATOR:
            switch(token.getAsc())
            {
            case Token::LEFT:
            {
                auto [a,b] = getTwoTokens(); 
                if      (str == "+") res = a + b;
                else if (str == "-") res = a - b;
                else if (str == "*") res = a * b;
                else if (str == "/") res = a / b;
                else if (str == "^") res = std::pow(a,b);
                else    throw SyntaxError("Unknown operator!");
                break;
            }
            case Token::RIGHT:
            {
                auto a = getOneToken();
                if   (str == "-") res = -a;
                else throw SyntaxError("Unknown operator!");
                break;
            }
            }
            stack.push(res);
            break;
        case Token::FUNCTION:
            if(str == "log") 
            {
                auto [a,b] = getTwoTokens();
                res = std::log(b) / std::log(a);
            }
            else if(str == "ln")
            {
                auto a = getOneToken();
                res = std::log(a);
            }
            else if(str == "lg")
            {
                auto a = getOneToken();
                res = std::log10(a);
            }
            else if(str == "max")
            {
                auto[a,b] = getTwoTokens();
                res = a > b ? a : b;
            }
            else if(str == "min")
            {
                auto[a,b] = getTwoTokens();
                res = a < b ? a : b;
            }
            else if(str == "sqrt")
            {
                auto a = getOneToken();
                res = std::sqrt(a);
            }
            else if(str == "sin")
            {
                auto a = getOneToken();
                res = std::sin(a);
            }
            else if(str == "cos")
            {
                auto a = getOneToken();
                res = std::cos(a);
            }
            else if (str == "tg")
            {
                auto a = getOneToken();
                res = std::tan(a);
            }
            else if (str == "ctg")
            {
                auto a = getOneToken();
                res = 1 / std::tan(a);
            }
            else
                throw SyntaxError("Unknown function!");
            stack.push(res);
            break;
        default:
            break;
        } 
    }
    if(stack.size() > 1) throw SyntaxError({});
    return stack.top();
}
