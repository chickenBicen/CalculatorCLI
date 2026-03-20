//
// Created by chice on 3/20/2026.
//

#ifndef CALC_CUSTOM_ERRORS_H
#define CALC_CUSTOM_ERRORS_H
#include <exception>
#include <string>

class CalculatorError : public std::exception {
protected:
    std::string msg;

public:
    explicit CalculatorError(std::string msg) : msg(msg) {
    }

    char const *what() const noexcept override { return msg.c_str(); }
};

class ParseError : public CalculatorError {
public:
    explicit ParseError(std::string msg) : CalculatorError(msg) {
    }
};

class MathError : public CalculatorError {
public:
    explicit MathError(std::string msg) : CalculatorError(msg) {
    }
};

#endif //CALC_CUSTOM_ERRORS_H