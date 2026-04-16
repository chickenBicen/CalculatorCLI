//
// Created by chice on 3/19/2026.
//

#include "../include/Lexer.h"

#include <iostream>
#include <ostream>
#include <stdexcept>
#include <unordered_map>
#include <algorithm>

std::unordered_map<std::string, double> constants{{"pi", 3.141592653589793}, {"e", 2.718281828459045}};

Token Lexer::nextToken()
{
    //TODO make support for vectors using vectmatlib and <> notation
    std::string num;
    // Keep track of last token type (initially None)
    TokenType lastType = lastToken.getType(); // assume lastToken is a member variable

    while (pos < line.length())
    {
        char c = line[pos];

        if (isspace(c))
        {
            pos++;
            continue;
        }

        // Number (possibly negative)
        if (isdigit(c) || (c == '-' && (lastType == TokenType::Operator || lastType == TokenType::LeftParen ||
                                        lastType == TokenType::None)))
        {
            bool isNegative = false;
            if (c == '-')
            {
                // this is for if the number is negative then go set bool true
                isNegative = true;
                pos++;
            }

            while (pos < line.length() && (isdigit(line[pos]) || line[pos] == '.'))
            {
                // keep going until you encounter something that isnt a number
                num += line[pos];
                pos++;
            }

            if (isNegative)
                num = "-" + num;
            lastToken = Token(TokenType::Number, num); // token is now the token that we made
                                                       // with the numbers obviously
            return lastToken;
        }

        if (line.substr(pos, 2) == "pi")
        {
            pos += 2;
            lastToken = Token(TokenType::Constant, constants["pi"]);
            return lastToken;
        }

        if (line.substr(pos, 1) == "e")
        {
            pos += 1;
            lastToken = Token(TokenType::Constant, constants["e"]);
            return lastToken;
        }

        // Functions
        if (line.substr(pos, 4) == "sqrt")
        {
            pos += 4;
            lastToken = Token(TokenType::Function, "sqrt");
            return lastToken;
        }

        if (line.substr(pos, 3) == "sin")
        {
            pos += 3;
            lastToken = Token(TokenType::Function, "sin");
            return lastToken;
        }

        if (line.substr(pos, 3) == "cos")
        {
            pos += 3;
            lastToken = Token(TokenType::Function, "cos");
            return lastToken;
        }

        if (line.substr(pos, 3) == "log")
        {
            pos += 3;
            lastToken = Token(TokenType::Function, "log");
            return lastToken;
        }

        if (line.substr(pos, 2) == "ln")
        {
            pos += 2;
            lastToken = Token(TokenType::Function, "ln");
            return lastToken;
        }

        if (c == '<')
        {
            size_t start = pos;

            auto it = std::find(line.begin() + pos + 1, line.end(), '>');
            if (it == line.end())
            {
                throw std::runtime_error("LEXER ERROR: INVALID VECTOR GROUPINGS");
            }

            size_t end = std::distance(line.begin(), it);

            // Extract everything inside < >
            std::string contents = line.substr(start + 1, end - start - 1);

            // Move past the closing '>'
            pos = end + 1;

            lastToken = Token(TokenType::Vector, contents);
            return lastToken;
        }

        // Operators
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%')
        {
            pos++;
            lastToken = Token(TokenType::Operator, std::string(1, c));
            return lastToken;
        }
        // Parentheses
        if (c == '(')
        {
            pos++;
            lastToken = Token(TokenType::LeftParen, "(");
            return lastToken;
        }
        if (c == ')')
        {
            pos++;
            lastToken = Token(TokenType::RightParen, ")");
            return lastToken;
        }

        // Unknown
        throw std::runtime_error("Unknown character");
    }

    pos = 0;
    lastToken = Token(TokenType::None, "");
    return Token(TokenType::End, "");
}

std::vector<Token> Lexer::tokenizeAll()
{
    std::vector<Token> tokens;

    while (true)
    {
        Token token = nextToken();
        if (token.getType() == TokenType::End)
        {
            break;
        }
        tokens.push_back(token);
    }

    return tokens;
}
