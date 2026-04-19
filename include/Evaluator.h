//
// Created by chice on 3/19/2026.
//

#ifndef CALC_EVALUATOR_H
#define CALC_EVALUATOR_H
#include "Parser.h"

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Token.h"
#include "Value.h"

#include <cmath>
#include <functional>

class Evaluator
{
  public:
    static double lastAnswer;
    Evaluator() = default;
    static std::unordered_map<std::string, Value> env;

    double evaluateRPN(std::vector<Token> tokens);
    double evaluate(const ParserResult& parsed);
};

#endif // CALC_EVALUATOR_H
