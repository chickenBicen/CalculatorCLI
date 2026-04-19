//
// Created by chice on 3/19/2026.
//

#ifndef CALC_TOKEN_H
#define CALC_TOKEN_H

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

enum class TokenType
{
    Number,
    Identifier,
    Equals,
    Function,
    Operator,
    LeftParen,
    RightParen,
    End,
    None
};

class Token
{
  private:
    TokenType type;
    std::string value;
    double numberValue{};

  public:
    Token(TokenType t, const std::string &v) : type(t), value(v)
    {
        if (type == TokenType::Number)
        {
            numberValue = std::stod(v);
        }
    }

    Token(TokenType t, double v) : type(t), numberValue(v)
    {
        std::ostringstream oss;
        oss << std::setprecision(15) << v;
        value = oss.str();
    }

    [[nodiscard]] TokenType getType() const
    {
        return type;
    }
    [[nodiscard]] std::string getValue() const
    {
        return value;
    }
    [[nodiscard]] double getNumberValue() const
    {
        return numberValue;
    }

    friend std::ostream &operator<<(std::ostream &os, const Token &token);
};

inline std::ostream &operator<<(std::ostream &os, const TokenType& t)
{
    switch (t)
    {
        case TokenType::Number: os << "Number"; break;
        case TokenType::Operator: os << "Operator"; break;
        case TokenType::Identifier: os << "Identifier"; break;
        case TokenType::Equals: os << "Equals"; break;
        case TokenType::Function: os << "Function"; break;
        case TokenType::LeftParen: os << "LeftParen"; break;
        case TokenType::RightParen: os << "RightParen"; break;
        case TokenType::End: os << "End"; break;
        case TokenType::None: os << "None"; break;
    }
    return os;
}

inline std::ostream &operator<<(std::ostream &os, const Token &t)
{
    os << t.value;
    return os;
}

#endif // CALC_TOKEN_H
