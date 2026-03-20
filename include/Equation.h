//
// Created by chice on 3/19/2026.
//

#ifndef UNTITLED_EQUATION_H
#define UNTITLED_EQUATION_H

#include <string>
#include <vector>

class Equation {
private:
    std::string line;
    std::vector<std::string> tokens;
    void tokenize();
    int precedence(const std::string& op);

public:
    Equation(std::string line);

    std::vector<std::string> infixToPostfix();
    double evaluate();

};


#endif //UNTITLED_EQUATION_H