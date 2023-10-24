#pragma once
#include <string>
#include <vector>
#include <map>
#include "Token.hpp"
#include "SyntaxError.hpp"

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
        S0, // Стартовое
        S1, // Токенизация скобки/оператора
        S2, // Запись целого числа в буфер
        S3, // Запись floating-point числа в буфер
        S4, // Запись функции в буфер
        S5  // Токенизация записанного числа/функции из буфера
    };

    State state;
    std::string ops = "+-*^/%";
};