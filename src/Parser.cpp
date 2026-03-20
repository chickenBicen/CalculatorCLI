//
// Created by chice on 3/19/2026.
//

#include "../include/Parser.h"
#include "../include/Token.h"
#include "../Custom_Errors.h"

#include <iostream>
#include <string>
#include <cmath>

enum class Assoc {
    Left,
    Right
};

Assoc getAssociativity(const Token &t) {
    if (t.getValue() == "^") {
        return Assoc::Right;
    } else {
        return Assoc::Left;
    }
}

int getPrecedence(const Token &t) {
    if (t.getType() != TokenType::Operator) {
        return 0;
    }
    if (t.getValue() == "+" || t.getValue() == "-")
        return 1;
    if (t.getValue() == "*" || t.getValue() == "/")
        return 2;
    if (t.getValue() == "^")
        return 3;
    return 0;
}

void Parser::checkParentheses() const {
    std::stack<Token> tokenStack;

    for (Token t: tokens) {
        if (t.getValue() == "(") {
            tokenStack.push(t);
        } else if (t.getValue() == ")") {
            if (tokenStack.empty()) {
                throw ParseError("Invalid Groupings!");
            }
            tokenStack.pop();
        }
    }

    if (!tokenStack.empty()) {
        throw ParseError("Invalid Groupings!");
    }
}

void Parser::checkOperators() const {
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i].getType() != TokenType::Operator) {
            continue;
        }
        if (i + 1 < tokens.size() && tokens[i + 1].getType() == TokenType::Operator) {
            throw MathError("MATH ERROR: Consecutive Operators!");
        }

        if (i == 0) {
            throw MathError("MATH ERROR: Starting with an Operator doesnt make sense!");
        }

        if (i == tokens.size() - 1) {
            throw MathError("MATH ERROR: Ending with an operator doesnt make sense either!");
        }

        if (i < tokens.size() - 1 && tokens[i].getValue() == "/" && tokens[i + 1].getValue() == "0") {
            throw MathError("MATH ERROR: Division by zero!");
        }
    }
}

bool associativityCheck(const Token &t, std::stack<Token> &operatorStack) {
    return ((getAssociativity(t) == Assoc::Left && getPrecedence(operatorStack.top()) >= getPrecedence(t)) ||
            (getAssociativity(t) == Assoc::Right && getPrecedence(operatorStack.top()) > getPrecedence(t)));
}

std::vector<Token> Parser::parse() const {
    std::stack<Token> operatorStack;
    std::vector<Token> output;

    checkOperators();
    checkParentheses();

    for (int i = 0; i < tokens.size(); i++) {
        Token t = tokens[i];
        if (t.getType() == TokenType::Number || t.getType() == TokenType::Constant) {
            output.push_back(t);
            if (tokens[i - 1].getType() == TokenType::RightParen) {
                output.push_back(Token(TokenType::Operator, "*"));
            } else if (tokens[i + 1].getType() == TokenType::LeftParen) {
                operatorStack.emplace(TokenType::Operator, "*");
            }

            if (t.getType() == TokenType::Constant) {
                continue;
            }

            if (tokens[i + 1].getType() == TokenType::Constant) {
                operatorStack.emplace(TokenType::Operator, "*");
            }
        } else if (t.getType() == TokenType::Function) {
            operatorStack.push(t);
        } else if (t.getType() == TokenType::LeftParen) {
            operatorStack.push(t);
        } else if (t.getType() == TokenType::RightParen) {
            while (!operatorStack.empty() &&
                   operatorStack.top().getType() != TokenType::LeftParen) {
                output.push_back(operatorStack.top());
                operatorStack.pop();
            }

            if (operatorStack.empty()) {
                throw ParseError("Invalid Groupings!");
            }

            operatorStack.pop(); // pop '('

            // If a function is on top, pop it too
            if (!operatorStack.empty() &&
                operatorStack.top().getType() == TokenType::Function) {
                output.push_back(operatorStack.top());
                operatorStack.pop();
            }
        } else if (t.getType() == TokenType::Operator) {
            while (!operatorStack.empty() && associativityCheck(t, operatorStack)) {
                output.push_back(operatorStack.top());
                operatorStack.pop();
            }

            operatorStack.push(t);
        } else {
            throw ParseError("Unknown token in parser");
        }
    }

    while (!operatorStack.empty()) {
        if (operatorStack.top().getType() == TokenType::LeftParen ||
            operatorStack.top().getType() == TokenType::RightParen) {
            throw ParseError("Invalid Groupings!");
        }

        output.push_back(operatorStack.top());
        operatorStack.pop();
    }

    return output;
}
