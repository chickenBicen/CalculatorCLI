//
// Created by chice on 3/19/2026.
//

#ifndef CALC_LEXER_H
#define CALC_LEXER_H

#include <vector>

#include "../include/Token.h"

class Lexer {
private:
    std::string line;
    size_t pos;
    Token lastToken;

public:
    explicit Lexer(const std::string &input) : line(input), pos(0), lastToken(TokenType::None, "") {
    };

    Token nextToken();

    std::vector<Token> tokenizeAll();
};


#endif //CALC_LEXER_H
