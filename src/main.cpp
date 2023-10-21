#include "Tokenizer.hpp"
#include "RPN.hpp"
#include <iostream>

int main()
{
    TokenizerFSM tokenizer;
    std::vector<Token> tokensInfix, tokensRPN;

    std::string expr = "4*1.25+(2-3^5)*1.23";
    std::cout << "Expression: " << expr << std::endl;

    tokenizer.tokenize(expr, tokensInfix);
    for(auto& i : tokensInfix) std::cout << i.tokenStr << ", type = " << i.type << "\n"; 

    shuntingYard(tokensInfix, tokensRPN);
    std::cout << "Reverse Polish Notation: ";
    for(auto& i : tokensRPN) std::cout << i.tokenStr << " "; 
    std::cout << "\n";

    std::cout << "Answer: " << countRPN(tokensRPN) << "\n";

    return 0;
}