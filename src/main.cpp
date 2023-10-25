#include "Tokenizer.hpp"
#include "RPN.hpp"
#include <iostream>

int main()
{
    std::vector<Token> tokensInfix, tokensRPN;

    std::string expr = "123+(2/(3.14))*(sqrt(0.1*10^(-3)/0.02))";
    std::cout << "Expression: " << expr << std::endl;

    try
    {
        tokenize(expr, tokensInfix);
        for(auto& i : tokensInfix) std::cout << i.getStr() << ", type = " << i.getType() << ", associative = " << i.getAsc() << "\n";

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