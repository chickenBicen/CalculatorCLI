//
// Created by chice on 3/19/2026.
//

#ifndef CALC_PARSER_H
#define CALC_PARSER_H

#include <stack>
#include "../include/Token.h"
#include <vector>

class Parser {
public:
    explicit Parser(const std::vector<Token> &tokens) : tokens(tokens) {
    };

    void checkParentheses() const;

    void checkOperators() const;

    std::vector<Token> parse() const;

private:
    std::vector<Token> tokens;
};


#endif //CALC_PARSER_H
