//
// Created by chice on 3/19/2026.
//

#include "../include/Evaluator.h"

#include <cmath>
#include <stack>
#include<string>
#include <unordered_map>
#include <functional>

#include "../Custom_Errors.h"

double Evaluator::lastAnswer = 0.0;

std::unordered_map<std::string, std::function<double(double)>> functions = {
    {"sqrt", sqrt},
    {"sin", sin},
    {"cos", cos},
    {"log", log},
    {"log10", log10}
};

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
            double a = tokenStack.top().getNumberValue();
            tokenStack.pop();
            tokenStack.emplace(TokenType::Number, functions[t.getValue()](a));
        }
    }
    lastAnswer = tokenStack.top().getNumberValue();
    return tokenStack.top().getNumberValue();
}
