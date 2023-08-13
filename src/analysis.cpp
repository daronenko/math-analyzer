#include "analysis.h"


long double Analysis::derivative(
    const std::deque<Tokens::Token> postfix_func_tokens,
    const double x,
    const double accuracy
) {
    return (Algo::compute(Config::postfix_func_tokens, x + accuracy / 2)
            - Algo::compute(Config::postfix_func_tokens, x - accuracy / 2))
            / accuracy;
}

std::vector<double> Analysis::get_extremes(
    const std::deque<Tokens::Token> postfix_func_tokens,
    double start,
    const double end,
    const double accuracy
) {
    std::vector<double> extremes;
    
    while (start <= end) {
        if (abs(derivative(postfix_func_tokens, start, accuracy)) <= accuracy) {
            extremes.push_back(start);
        }

        start += accuracy;
    }

    return extremes;
}

double Analysis::get_root(
    const std::deque<Tokens::Token> postfix_func_tokens,
    double start,
    double end,
    const double accuracy
) {
    double x;
    while((end - start) / 2 > accuracy) {
        x = (start + end) / 2;
        if (Algo::compute(postfix_func_tokens, start) * Algo::compute(postfix_func_tokens, x) > 0) {
            start = x;
        } else {
            end = x;
        }
    }

    return x;
}

double Analysis::get_integral(
    const std::deque<Tokens::Token> postfix_func_tokens,
    const double start,
    const double end,
    const double accuracy
) {
    double n = 1;
    double integral, integral_prev;  

    while (std::abs(integral - integral_prev) < accuracy) {
        double h = (end - start) / n;
        integral_prev = integral;
        integral = 0;

        for (int i = 0; i < n; i++) {
            double x = start + (i + 0.5) * h;
            integral += Algo::compute(postfix_func_tokens, x);
        }

        integral *= h;
        n *= 2;
    }

    return integral;

}
