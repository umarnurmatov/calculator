#include <iostream>
#include "Tokenizer.hpp"
#include "RPN.hpp"

int main()
{
    std::vector<Token> tokensInfix, tokensRPN;

    std::string expr = "log2(23)+(-2/(3.14))*(sqrt(0.1*10^(-3)/0.02))";
    std::cout << "Expression: " << expr << std::endl;

    try
    {
        tokenize(expr, tokensInfix);
        for(auto& i : tokensInfix)
        {
            std::string type, asc;
            switch(i.getType())
            {
            case Token::OPERATOR:
                type = "OPERATOR";
                break;
            case Token::L_PARANTHESIS:
                type = "L_PARANTHESIS";
                break;
            case Token::R_PARANTHESIS:
                type = "R_PARANTHESIS";
                break;
            case Token::INT_LITERAL:
                type = "INT_LITERAL";
                break;
            case Token::FLOAT_LITERAL:
                type = "FLOAT_LITERAL";
                break;
            case Token::FUNCTION:
                type = "FUNCTION";
                break;
            case Token::SEPARATOR:
                type = "SEPARATOR";
                break;
            }

            switch(i.getAsc())
            {
            case Token::NONE:
                asc = "NONE";
                break;
            case Token::RIGHT:
                asc = "RIGHT";
                break;
            case Token::LEFT:
                asc = "LEFT";
                break;
            }
            std::cout << i.getStr() << "\t" << type << "\t" << asc << "\n";
        }

        shuntingYard(tokensInfix, tokensRPN);
        std::cout << "Reverse Polish Notation: ";
        for (auto &i : tokensRPN)
            std::cout << i.getStr() << " ";
        std::cout << "\n";

        std::cout << "Answer: " << countRPN(tokensRPN) << "\n";
    }
    catch(Error &e)
    {
        std::cerr << e.what() << "\n";
        exit(-1);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(-1);
    }

    return 0;
}