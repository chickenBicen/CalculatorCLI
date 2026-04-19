#include "../include/Evaluator.h"
#include "../include/Lexer.h"
#include "../include/Parser.h"
#include <cctype>
#include <iostream>
#include <limits>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

int main()
{
    while (true)
    {
        std::string str = "";

        std::cout << "enter your equation:: ";
        std::getline(std::cin, str);
        try
        {
            Lexer lexer(str);
            auto tokens = lexer.tokenizeAll();
            Parser parser(tokens);
            auto parsed = parser.parse();

            for (Token t : parsed)
            {
                std::cout << RED << t << " ";
            }
            std::cout << RESET << std::endl;

            Evaluator evaluator{};

            std::cout << GREEN << std::setprecision(15) << evaluator.evaluate(parsed) << "\n\n" << RESET;
        }
        catch (std::exception e)
        {
            std::cout << RED << e.what() << std::endl;
            continue;
        }
    }
}
