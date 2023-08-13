#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


namespace Tokens {

    extern const unsigned char MAX_ARGS_COUNT;
    
    extern std::string_view OPENING_BRACKETS;
    extern std::string_view CLOSING_BRACKETS;
    extern std::string_view WHITESPACES;
    extern std::string_view SEPARATORS;
    extern std::string_view LETTERS;
    extern std::string_view DIGIT_TOKENS;

    struct Operation {
        std::string_view name;
        const unsigned char args_count;
        const unsigned char priority;
        double(*exec)(std::vector<double>&);

        Operation(
            std::string_view name,
            const unsigned char args_count,
            const unsigned char priority,
            double(*exec)(std::vector<double>&)
        );
    };

    extern const std::unordered_map<char, Operation*> OPERATORS;
    extern const std::unordered_map<std::string_view, Operation*> FUNCS;

    struct Bracket {
        enum class Type {
            OPENING,
            CLOSING
        } type;
        
        const char bracket;
        const char matching;

        Bracket(Type type, const char bracket, const char matching);
    };

    extern const std::unordered_map<char, Bracket*> BRACKETS;

    struct Token {
        enum class Type {
            NONE,
            NUMBER,
            OPERATION,
            BRACKET,
            UNKNOWN_VAR
        } type;

        union {
            double number;
            const Operation *operation;
            const Bracket *bracket;
        } value;

        Token();
        Token(double number);
        Token(const Operation *operation);
        Token(const Bracket *bracket);
    };

    extern const std::unordered_map<std::string_view, const double> CONSTS;

}
