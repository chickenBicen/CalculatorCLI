//
// Created by chice on 4/19/2026.
//

#ifndef CALC_VALUE_H
#define CALC_VALUE_H
#include <functional>
#include <vector>

enum class ValueType
{
    Number, Function
};

struct Value
{
    ValueType type;
    double number;

    std::function<double(const std::vector<double>& arg)> func;
};

#endif // CALC_VALUE_H
