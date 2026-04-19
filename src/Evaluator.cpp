//
// Created by chice on 3/19/2026.
//

#include "../include/Evaluator.h"

#include <cmath>
#include <functional>
#include <stack>
#include <string>
#include <unordered_map>

#include "../Custom_Errors.h"

double Evaluator::lastAnswer = 0.0;

std::unordered_map<std::string, std::function<double(double)>> functions = {
    {"sqrt", sqrt}, {"sin", sin},     {"cos", cos},     {"log", log10},
    {"ln", log},    {"arcsin", asin}, {"arccos", acos}, {"arctan", atan}};

std::unordered_map<std::string, double> constants = {{"pi", 3.141592653589793}, {"e", 2.718281828459045}};

double Evaluator::evaluate(std::vector<Token> tokens)
{
    std::stack<Token> tokenStack;

    for (int i =0; i < tokens.size(); i++)
    {
        Token t = tokens[i];
        if (t.getType() == TokenType::Number)
        {
            tokenStack.push(t);
            continue;
        }

        if (constants.find(t.getValue()) != constants.end())
        {
            tokenStack.push(Token(TokenType::Number, constants[t.getValue()]));
            continue;
        }

        if (t.getType() == TokenType::Operator)
        {
            double a = tokenStack.top().getNumberValue();
            tokenStack.pop();
            double b = tokenStack.top().getNumberValue();
            tokenStack.pop();

            if (t.getValue() == "+")
            {
                tokenStack.emplace(TokenType::Number, b + a);
            }
            else if (t.getValue() == "-")
            {
                tokenStack.emplace(TokenType::Number, b - a);
            }
            else if (t.getValue() == "*")
            {
                tokenStack.emplace(TokenType::Number, b * a);
            }
            else if (t.getValue() == "/")
            {
                if (tokens[i+1].getNumberValue() == 0) throw MathError("Division by zero");
                tokenStack.emplace(TokenType::Number, b / a);
            }
            else if (t.getValue() == "^")
            {
                tokenStack.emplace(TokenType::Number, pow(b, a));
            }
            else if (t.getValue() == "%")
            {
                tokenStack.emplace(TokenType::Number, static_cast<double>(static_cast<int>(b) % static_cast<int>(a)));
            }
        }
        if (t.getType() == TokenType::Identifier)
        {
            if (tokenStack.empty()) throw MathError("Function missing argument");
            double a = tokenStack.top().getNumberValue();
            tokenStack.pop();
            tokenStack.emplace(TokenType::Number, functions[t.getValue()](a));
        }
    }
    lastAnswer = tokenStack.top().getNumberValue();
    if (lastAnswer < 1e-12)
    {
        lastAnswer = 0.0;
    }
    return lastAnswer;
}
