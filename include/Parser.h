//
// Created by chice on 3/19/2026.
//

#ifndef CALC_PARSER_H
#define CALC_PARSER_H

#include "../include/Token.h"
#include <stack>
#include <vector>

struct ParserResult
{
    std::vector<Token> rpn;
    bool isAssignment = false;
    std::string target;

};

class Parser
{
  public:
    explicit Parser(const std::vector<Token> &tokens) : tokens(tokens) {};

    void checkParentheses() const;

    void checkOperators() const;

    void checkVectorOperations() const; // not yet implemented

    [[nodiscard]] ParserResult parse() const;
    std::vector<Token> parseExpression(const std::vector<Token> &tokens) const;

  private:
    std::vector<Token> tokens;
};

#endif // CALC_PARSER_H
