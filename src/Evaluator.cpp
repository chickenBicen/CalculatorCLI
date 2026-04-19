//
// Created by chice on 3/19/2026.
//

#include "../include/Evaluator.h"
#include "../include/Value.h"

#include <cmath>
#include <functional>
#include <stack>
#include <string>
#include <unordered_map>

#include "../Custom_Errors.h"

double Evaluator::lastAnswer = 0.0;

Value makeUnaryFunction(std::function<double(double)> f)
{
    return Value{ValueType::Function, 0, [f](const std::vector<double> &args)
                 {
                     if (args.size() != 1)
                         throw MathError("Function expects 1 argument");
                     return f(args[0]);
                 }};
}

Value makeBinaryFunction(std::function<double(double, double)> f)
{
    return Value{ValueType::Function, 0, [f](const std::vector<double> &args)
                 {
                     if (args.size() != 2)
                         throw MathError("Function expects 2 argument");
                     return f(args[0], args[1]);
                 }};
}

std::unordered_map<std::string, Value> createEnv()
{
    std::unordered_map<std::string, Value> env = {{"pi", Value{ValueType::Number, std::numbers::pi}},
                                                  {"e", Value{ValueType::Number, std::numbers::e}},
                                                  {"sqrt", makeUnaryFunction(sqrt)},
                                                  {"log", makeUnaryFunction(log10)},
                                                  {"ln", makeUnaryFunction(log)},
                                                  {"sin", makeUnaryFunction(sin)},
                                                  {"cos", makeUnaryFunction(cos)},
                                                  {"tan", makeUnaryFunction(tan)},
                                                  {"arcsin", makeUnaryFunction(asin)},
                                                  {"arccos", makeUnaryFunction(acos)},
                                                  {"arctan", makeUnaryFunction(atan)}};

    env["max"] = Value{ValueType::Function, 0, [](const std::vector<double> &args)
                       {
                           if (args.empty())
                           {
                               throw MathError("Function expects an argument");
                           }
                           double m = args[0];
                           for (size_t i = 1; i < args.size(); i++)
                           {
                               m = std::max(m, args[i]);
                           }
                           return m;
                       }};

    return env;
}

std::unordered_map<std::string, double> constants = {{"pi", std::numbers::pi}, {"e", std::numbers::e}};
std::unordered_map<std::string, Value> envr = createEnv();

void checkEnvironment()
{
    for (const auto& [key, value] : envr) {
        std::cout << key << ": " << value.number << std::endl;
    }
}

double Evaluator::evaluateRPN(std::vector<Token> tokens)
{

    std::stack<Token> tokenStack;

    for (int i = 0; i < tokens.size(); i++)
    {
        Token t = tokens[i];
        if (t.getType() == TokenType::Number)
        {
            tokenStack.push(t);
            continue;
        }

        if (envr.find(t.getValue()) != envr.end() && envr[t.getValue()].type != ValueType::Function)
        {
            tokenStack.push(Token(TokenType::Number, envr[t.getValue()].number));
            continue;
        }

        if (t.getType() == TokenType::Operator)
        {
            if (tokenStack.size() < 2)
            {
                throw MathError("Operator expects at least 2 arguments");
            }
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
                if (a == 0)
                    throw MathError("Division by zero");
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
        if (t.getType() == TokenType::Function)
        {
            if (tokenStack.empty())
                throw MathError("Function missing argument");

            double a = tokenStack.top().getNumberValue();
            tokenStack.pop();

            auto it = envr.find(t.getValue());
            if (it == envr.end() || it->second.type != ValueType::Function)
                throw MathError("Unknown function");

            double result = it->second.func({a});
            tokenStack.emplace(TokenType::Number, result);
        }
    }
    lastAnswer = tokenStack.top().getNumberValue();
    if (lastAnswer < 1e-12)
    {
        lastAnswer = 0.0;
    }
    return lastAnswer;
}

double Evaluator::evaluate(const ParserResult& parsed)
{
    double result = evaluateRPN(parsed.rpn);

    if (parsed.isAssignment)
    {
        envr[parsed.target] = Value{ValueType::Number, result};
    }

    return result;
}
