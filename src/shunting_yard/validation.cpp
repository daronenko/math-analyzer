#include "shunting_yard/validation.h"

#include <iostream>


void Validation::validate_alphabet(std::string_view expr) {
    for (const char &item: expr) {
        if (!(
            item == '.' ||
            'a' <= item && item <= 'z' ||
            'A' <= item && item <= 'Z' ||
            '0' <= item && item <= '9' ||
            Tokens::WHITESPACES.find(item) != std::string::npos ||
            Tokens::SEPARATORS.find(item) != std::string::npos ||
            Tokens::BRACKETS.contains(item) ||
            Tokens::OPERATORS.contains(item)
        )) {
            throw Errors::AlphabetError("Unknown symbol!");
        }
    }
}


void Validation::validate_brackets(std::string_view expr) {
    std::stack<char> stack;
    const Tokens::Bracket *bracket;
    
    for (const char &item: expr) {
        if (Tokens::BRACKETS.contains(item)) {
            bracket = Tokens::BRACKETS.at(item);
            
            if (bracket->type == Tokens::Bracket::Type::OPENING) {
                stack.push(item);
            } else if (stack.size() != 0 && bracket->matching == stack.top()) {
                stack.pop();
            } else {
                throw Errors::BracketsSequenceOrderError("Invalid brackets sequence!");
            }
        }
    }

    if (stack.size()) {
        throw Errors::BracketsSequenceOrderError(
            "The number of opening parentheses does not match the number of closing parentheses!"
        );
    }
}

void Validation::validate_tokens_order(std::string_view expr) {
    bool is_start {true};
    bool is_operator_possible {true};
    bool is_closing_bracket_possible {false};

    for (const char &item: expr) {
        if (
            is_start &&
            (item == '*' ||
            item == '/' ||
            item == '^')
        ) {
            throw Errors::OperatorsOrderError("The expression starts with an invalid operation!");
        
        } else if (
            !is_operator_possible &&
            Tokens::OPERATORS.contains(item)
        ) {
            throw Errors::OperatorsOrderError("The expression contains two operators in a row!");
        
        } else if (
            !is_closing_bracket_possible &&
            (Tokens::BRACKETS.contains(item) && Tokens::BRACKETS.at(item)->type == Tokens::Bracket::Type::CLOSING ||
            Tokens::SEPARATORS.find(item) != std::string::npos)
        ) {
            throw Errors::OperatorsOrderError("The expression ends with the operator!");
        } 

        if (Tokens::WHITESPACES.find(item) != std::string::npos) {
            continue;
        
        } else if (Tokens::OPERATORS.contains(item)) {
            is_start = false;
            is_operator_possible = false;
            is_closing_bracket_possible = false;
        
        } else if (std::isalpha(item) || std::isdigit(item) || item == '.') {
            is_start = false;
            is_operator_possible = true;
            is_closing_bracket_possible = true;

        } else if (
            Tokens::SEPARATORS.find(item) != std::string::npos ||
            Tokens::BRACKETS.contains(item) &&
            Tokens::BRACKETS.at(item)->type == Tokens::Bracket::Type::OPENING
        ) {
            is_start = true;
            is_operator_possible = true;
            is_closing_bracket_possible = false;
        }
    }

    if (
        expr.ends_with("+") ||
        expr.ends_with("-") ||
        expr.ends_with("*") ||
        expr.ends_with("/") ||
        expr.ends_with("^")
    ) {
        throw Errors::OperatorsOrderError("The expression ends with the operator!");
    }
}

void Validation::validate_function(std::string_view expr) {
    std::string_view func_name {expr.substr(0, expr.find_first_not_of(Tokens::LETTERS))};
    if (!Tokens::FUNCS.contains(func_name)) {
        throw Errors::UnknownFunctionError("Unknown function!");
    }

    unsigned char args_count {1};
    size_t arg_start {expr.find_first_of(Tokens::OPENING_BRACKETS) + 1};
    for (size_t i {expr.find_first_of(Tokens::OPENING_BRACKETS)}; i < expr.length() - 1; ++i) {
        if (Tokens::SEPARATORS.find(expr[i]) != std::string::npos) {
            ++args_count;
            validate_brackets(expr.substr(arg_start, i - arg_start));
            arg_start = i + 1;
        }
    }
    validate_brackets(expr.substr(arg_start, expr.length() - arg_start - 1));

    if (args_count != Tokens::FUNCS.at(func_name)->args_count) {
        throw Errors::FunctionArgsNumberError("Invalid args number!");
    }
}

void Validation::validate_var(std::string_view expr) {
    if (
        Tokens::CONSTS.find(expr) == Tokens::CONSTS.end() &&
        Config::unknown_var != expr
    ) {
        throw Errors::UnknownVariableError("Unknown variable!");
    }
}

size_t Validation::find_closing_bracket(std::string_view expr, size_t opening_bracket) {
    std::stack<char> stack;
    const Tokens::Bracket *bracket;
    
    stack.push(expr[opening_bracket]);
    size_t i {opening_bracket + 1};
    while (stack.size() != 0) {
        if (Tokens::BRACKETS.contains(expr[i])) {
            bracket = Tokens::BRACKETS.at(expr[i]);
            
            if (bracket->type == Tokens::Bracket::Type::OPENING) {
                stack.push(expr[i]);
            } else if (stack.size() != 0 && bracket->matching == stack.top()) {
                stack.pop();
            } else {
                throw Errors::BracketsSequenceOrderError("Invalid brackets sequence!");
            }
        }
        ++i;
    }

    return i - 1;
}

void Validation::validate_letter_combos(std::string_view expr) {
    size_t start {expr.find_first_of(Tokens::LETTERS)};
    size_t end;
    size_t nearest_char;
    const Tokens::Bracket *bracket;
    while (start != std::string::npos) {
        end = expr.find_first_not_of(Tokens::LETTERS, start);

        nearest_char = expr.find_first_not_of(Tokens::WHITESPACES, end);
        if (
            Tokens::BRACKETS.contains(expr[nearest_char]) &&
            Tokens::BRACKETS.at(expr[nearest_char])->type == Tokens::Bracket::Type::OPENING
        ) {        
            bracket = Tokens::BRACKETS.at(expr[nearest_char]);
            validate_function(expr.substr(start, find_closing_bracket(expr, nearest_char) - start + 1));
        } else {
            validate_var(expr.substr(start, end - start));
        }
        start = expr.find_first_of(Tokens::LETTERS, end);
    }
}

void Validation::validate_var_format(std::string_view expr) {
   if (Tokens::CONSTS.contains(expr)) {
        throw Errors::InvalidVariableFormatError("Invalid variable format!");
    } 
}
