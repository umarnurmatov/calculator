#pragma once
#include <vector>
#include "Token.hpp"

enum State
{
    S0, // Стартовое
    S1, // Токенизация скобки/оператора
    S2, // Запись целого числа в буфер
    S3, // Запись floating-point числа в буфер
    S4, // Запись функции в буфер
    S5  // Токенизация записанного числа/функции из буфера
};


void tokenize(const std::string &expr, std::vector<Token> &tokens);