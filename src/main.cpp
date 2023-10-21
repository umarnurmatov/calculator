#include "Tokenizer.hpp"
#include "RPN.hpp"
#include <iostream>

int main()
{
    TokenizerFSM tokenizer;
    std::vector<Token> tokensInfix, tokensRPN;

    std::string expr = "4*1.25+(-2-3^5)*1.23";
    std::cout << "Expression: " << expr << std::endl;

    try
    {
        tokenizer.tokenize(expr, tokensInfix);
        for(auto& i : tokensInfix) std::cout << i.getStr() << ", type = " << i.getType() << ", associative = " << i.getAsc() << "\n";

        shuntingYard(tokensInfix, tokensRPN);
    }
    catch(CustomException &e)
    {
        std::cerr << e.what() << "\n";
        exit(-1);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(-1);
    }

    std::cout << "Reverse Polish Notation: ";
    for(auto& i : tokensRPN) std::cout << i.getStr() << " "; 
    std::cout << "\n";

    std::cout << "Answer: " << countRPN(tokensRPN) << "\n";

    return 0;
}