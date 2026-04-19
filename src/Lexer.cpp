//
// Created by chice on 3/19/2026.
//

#include "../include/Lexer.h"
#include "../include/Evaluator.h"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <unordered_map>
Token Lexer::nextToken()
{
    // TODO make support for vectors using vectmatlib and <> notation
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

        if (c == 'a')
        {
            if (line.substr(pos, 3) == "ans")
            {
                pos+=3;
                lastToken = Token(TokenType::Number, Evaluator::lastAnswer);
                return lastToken;
            }
        }

        if (c=='=')
        {
            pos++;
            lastToken = Token(TokenType::Equals, "=");
            return lastToken;
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

        //makes identifiers from things like sin, pi, x, x1, _x, abc_function, f, etc.
        if (isalpha(c))
        {
            std::string ident;

            while (pos < line.length() && (isalnum(line[pos]) || line[pos] == '_'))
            {
                ident += line[pos];
                pos++;
            }

            lastToken = Token(TokenType::Identifier, ident);
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
