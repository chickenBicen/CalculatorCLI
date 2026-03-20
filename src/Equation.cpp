#include "../include/Equation.h"

#include <cctype>
#include <sstream>
#include <vector>
#include <stack>
#include <cmath>

Equation::Equation(std::string eq) {
    this->line = eq;
    tokenize();
}

void Equation::tokenize() {
    std::string num = "";

    for (char c: line) {
        if (isdigit(c)) {
            // part of a number
            num += c;
            continue;
        }

        if (!num.empty()) {
            // push the number we've collected before the non number
            tokens.push_back(num);
            num = "";
        }

        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '[' || c == ']') {
            tokens.push_back(std::string(1, c)); // push operator or parenthesis
        }
    }

    if (!num.empty()) {
        // push last number if any
        tokens.push_back(num);
    }
}

int Equation::precedence(const std::string &op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}

std::vector<std::string> Equation::infixToPostfix() {
    std::stack<std::string> operatorStack;
    std::vector<std::string> output;

    for (std::string s: tokens) {
        if (isdigit(s[0])) {
            // number
            output.push_back(s);
        } else if (s == "(") {
            operatorStack.push(s);
        } else if (s == ")") {
            while (!operatorStack.empty() && operatorStack.top() != "(") {
                output.push_back(operatorStack.top());
                operatorStack.pop();
            }
            if (!operatorStack.empty()) operatorStack.pop(); // pop '('
        } else if (s == "[") {
            operatorStack.push("sqrt"); // function
            operatorStack.push("["); // grouping
        } else if (s == "]") {
            while (!operatorStack.empty() && operatorStack.top() != "[") {
                output.push_back(operatorStack.top());
                operatorStack.pop();
            }

            if (!operatorStack.empty()) operatorStack.pop(); // remove "["

            // NOW handle sqrt
            if (!operatorStack.empty() && operatorStack.top() == "sqrt") {
                output.push_back(operatorStack.top());
                operatorStack.pop();
            }
        } else {
            // operator
            while (!operatorStack.empty() &&
                   precedence(operatorStack.top()) >= precedence(s)) {
                output.push_back(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.push(s);
        }
    }

    while (!operatorStack.empty()) {
        output.push_back(operatorStack.top());
        operatorStack.pop();
    }

    return output;
}

double Equation::evaluate() {
    std::vector<std::string> postfix = infixToPostfix();
    std::stack<double> stack;

    for (std::string token: postfix) {
        if (isdigit(token[0]) || token[0] == '-') {
            stack.push(std::stod(token));
            continue;
        }

        if (token == "sqrt") {
            double a = stack.top();
            stack.pop();

            double result = sqrt(a);
            stack.push(result);
            continue;
        }

        double a = stack.top();
        stack.pop();
        double b = stack.top();
        stack.pop();

        if (token == "*") {
            stack.push(a * b);
        }
        if (token == "/") {
            stack.push(a / b);
        }
        if (token == "-") {
            stack.push(a - b);
        }
        if (token == "+") {
            stack.push(a + b);
        }
    }

    return stack.top();
}
