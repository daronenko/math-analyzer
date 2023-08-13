#pragma once

#include "shunting_yard/algo.h"
#include "shunting_yard/tokens.h"
#include "config.h"

#include <vector>
#include <cmath>


namespace Analysis {

    long double derivative(
        const std::deque<Tokens::Token> postfix_func_tokens,
        const double x,
        const double accuracy
    );

    std::vector<double> get_extremes(
        const std::deque<Tokens::Token> postfix_func_tokens,
        double start,
        const double end,
        const double accuracy
    );
    
    double get_root(
        const std::deque<Tokens::Token> postfix_func_tokens,
        double start,
        double end,
        const double accuracy
    );

    double get_integral(
        const std::deque<Tokens::Token> postfix_func_tokens,
        const double start,
        const double end,
        const double accuracy
    );

}