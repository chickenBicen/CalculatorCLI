//
// Created by chice on 3/19/2026.
//

#include "../include/Evaluator.h"

#include <cmath>
#include <stack>
#include<string>
#include <unordered_map>

#include "../Custom_Errors.h"

double Evaluator::evaluate(std::vector<Token> tokens) {
    std::stack<Token> tokenStack;

    for (Token t: tokens) {
        if (t.getType() == TokenType::Number || t.getType() == TokenType::Constant) {
            tokenStack.push(t);
            continue;
        }

        if (t.getType() == TokenType::Operator) {
            double a = tokenStack.top().getNumberValue();
            tokenStack.pop();
            double b = tokenStack.top().getNumberValue();
            tokenStack.pop();

            if (t.getValue() == "+") {
                tokenStack.emplace(TokenType::Number, b + a);
            } else if (t.getValue() == "-") {
                tokenStack.emplace(TokenType::Number, b - a);
            } else if (t.getValue() == "*") {
                tokenStack.emplace(TokenType::Number, b * a);
            } else if (t.getValue() == "/") {
                tokenStack.emplace(TokenType::Number, b / a);
            } else if (t.getValue() == "^") {
                tokenStack.emplace(TokenType::Number, pow(b, a));
            }
        }
        if (t.getType() == TokenType::Function) {
            if (t.getValue() == "sqrt") {
                double a = tokenStack.top().getNumberValue();
                tokenStack.pop();
                tokenStack.emplace(TokenType::Number, sqrt(a));
            }

            if (t.getValue() == "sin") {
                double a = tokenStack.top().getNumberValue();
                tokenStack.pop();
                tokenStack.emplace(TokenType::Number, sin(a));
            } else if (t.getValue() == "cos") {
                double a = tokenStack.top().getNumberValue();
                tokenStack.pop();
                tokenStack.emplace(TokenType::Number, cos(a));
            }
        }
    }
    return tokenStack.top().getNumberValue();
}
