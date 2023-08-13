#pragma once

#include "analysis.h"

#include <vector>


namespace Actions {

    void find_extremes();
    void find_root();
    void find_integral();

    void print_result(const std::string name, const double result);
    void print_result(const std::string name, const std::vector<double> result);

}