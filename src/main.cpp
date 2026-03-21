#include <iostream>
#include <cctype>
#include "../include/Lexer.h"
#include "../include/Parser.h"
#include "../include/Evaluator.h"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    Lexer lexer("3(3+3)");
    Parser parser(lexer.tokenizeAll());
    Evaluator evaluator{};
    for (Token t: lexer.tokenizeAll()) {
        std::cout << t;
    }
    std::cout << "\n";

    std::cout << "\n";

    for (Token t: parser.parse()) {
        std::cout << t;
    }

    std::cout << "\n";

    std::cout << std::setprecision(15) << evaluator.evaluate(parser.parse());
}
