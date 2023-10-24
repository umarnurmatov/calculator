#pragma once
#include <vector>
#include "Token.hpp"
#include "SyntaxError.hpp"

void shuntingYard(const std::vector<Token> &expr, std::vector<Token> &outQueue);

double countRPN(const std::vector<Token> &expr);