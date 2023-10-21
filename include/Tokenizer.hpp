#pragma once
#include <string>
#include <vector>
#include <map>
#include "Token.hpp"
#include "CustomException.hpp"

class TokenizerFSM
{

public:
    TokenizerFSM()
    : state(S0)
    {}

    void tokenize(std::string &expr, std::vector<Token> &tokens);

private:
    enum State
    {
        S0, //стартовое
        S1, //Токенизация скобки/оператора
        S2, //Запись целого числа
        S3, //Запись float числа
        S4  //Токенизация записанного числа и скобки/оператора
    };

    State state;
    std::string ops = "+-*^/%";
};