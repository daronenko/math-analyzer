#include "config.h"



const std::string Config::ARGUMENT_NAME {"ARGUMENT"};
const std::string Config::FUNCTION_NAME {"FUNCTION"};
const std::string Config::INTERVAL_NAME {"INTERVAL"};
const std::string Config::ACCURACY_NAME {"ACCURACY"};

std::string Config::unknown_var {"x"};

std::string Config::func {"x^2"};
std::deque<Tokens::Token> Config::postfix_func_tokens;

double Config::interval_start {-1};
double Config::interval_end {2};

double Config::accuracy {0.0001};


void Config::load_config() {
    std::ifstream in(CONFIG_FILE);

    std::string param;
    char equal_sign;

    std::string str_value;
    double value;

    while (!in.eof()) {
        in >> param;
        if (param == ARGUMENT_NAME) {
            in >> equal_sign >> str_value;
            if (str_value.length() != 1 || !std::isalpha(str_value[0])) {
                throw;
            }
            Config::unknown_var = str_value;
        } else if (param == FUNCTION_NAME) {
            in >> equal_sign >> str_value;
            Config::postfix_func_tokens = Algo::shunting_yard(str_value);
            Config::func = str_value;
        } else if (param == INTERVAL_NAME) {
            in >> equal_sign >> Config::interval_start >> Config::interval_end;
        } else if (param == ACCURACY_NAME) {
            in >> equal_sign >> Config::accuracy;
        } else {
            throw;
        }
    }

    in.close();
}

void Config::save_config() {
    std::ofstream out(CONFIG_FILE);

    out << ARGUMENT_NAME + std::string(" = ") << Config::unknown_var << std::endl;
    out << FUNCTION_NAME + std::string(" = ") << Config::func << std::endl;
    out << INTERVAL_NAME + std::string(" = ") << Config::interval_start << ' ' << Config::interval_end << std::endl;
    out << ACCURACY_NAME + std::string(" = ") << Config::accuracy;

    out.close();
}

std::string Config::get_str_param(std::string_view text) {
    if (text == ARGUMENT_NAME) {
        return " = " + unknown_var;
    } else if (text == FUNCTION_NAME) {
        return " = " + func;
    } else if (text == INTERVAL_NAME) {
        return " = [" + std::to_string(interval_start) + ", " + std::to_string(interval_end) + "]";
    } else if (text == ACCURACY_NAME) {
        return " = " + std::to_string(accuracy);
    } else {
        return std::string();
    }
}

double Config::get_double(std::string param) {
    double result;
    system("clear");
    printf("Enter the '%s': ", param.c_str());
    std::cin >> result;

    return result;
}

std::string Config::get_string(std::string param) {
    std::string result;
    system("clear");
    printf("Enter the '%s': ", param.c_str());
    std::cin >> result;

    return result;
}

void Config::set_arg(const std::string val) {
    Validation::validate_var_format(val);
    unknown_var = val;
    set_func(get_string(FUNCTION_NAME));
}

void Config::set_func(const std::string val) {
    postfix_func_tokens = Algo::shunting_yard(val);
    func = val;
}

void Config::set_interval(const double start, const double end) {
    if (start < end) {
        interval_start = start;
        interval_end = end;
    }
}

void Config::set_accuracy(const double val) {
    accuracy = val;
}
