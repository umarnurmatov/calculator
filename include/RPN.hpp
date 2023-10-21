#pragma once
#include <vector>
#include "Token.hpp"
#include "CustomException.hpp"

void shuntingYard(std::vector<Token> &expr, std::vector<Token> &outQueue);

double countRPN(std::vector<Token> &expr);