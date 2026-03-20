//
// Created by chice on 3/19/2026.
//

#ifndef CALC_EVALUATOR_H
#define CALC_EVALUATOR_H
#include <vector>

#include "Token.h"

class Evaluator {
public:
    Evaluator() = default;

    double evaluate(std::vector<Token> tokens);
};

#endif //CALC_EVALUATOR_H
