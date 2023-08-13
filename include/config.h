#pragma once

#include "shunting_yard/algo.h"
#include "shunting_yard/tokens.h"
#include "shunting_yard/tokenizer.h"
#include "shunting_yard/validation.h"
#include "ui/menu.h"

#include <deque>
#include <string>
#include <fstream>

#define CONFIG_FILE "../math-analyzer.conf"


namespace Config {

    extern const std::string ARGUMENT_NAME;
    extern const std::string FUNCTION_NAME;
    extern const std::string INTERVAL_NAME;
    extern const std::string ACCURACY_NAME;

    extern std::string unknown_var;

    extern std::string func;
    extern std::deque<Tokens::Token> postfix_func_tokens;

    extern double interval_start;
    extern double interval_end;

    extern double accuracy;

    void load_config();
    void save_config();

    std::string get_str_param(std::string_view text);

    double get_double(std::string param);
    std::string get_string(std::string param);
    
    void set_arg(const std::string val);
    void set_func(const std::string val);
    void set_interval(const double start, const double end);
    void set_accuracy(const double val);

}