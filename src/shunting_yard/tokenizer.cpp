#include "shunting_yard/tokenizer.h"
#include "shunting_yard/tokens.h"
#include "shunting_yard/validation.h"
#include "config.h"


void Tokenizer::tokenize(std::string expr, std::vector<Tokens::Token> &result) {
    std::transform(expr.begin(), expr.end(), expr.begin(), ::tolower);
    
    Validation::validate_alphabet(expr);
    Validation::validate_brackets(expr);
    Validation::validate_tokens_order(expr);
    Validation::validate_letter_combos(expr);
    
    size_t start {expr.find_first_not_of(Tokens::WHITESPACES)};
    size_t end;
    size_t closing_bracket;
    std::string_view name;
    unsigned char args_count;
    
    while (start != std::string::npos) {
        if (std::isdigit(expr[start])) {
            end = expr.find_first_not_of(Tokens::DIGIT_TOKENS, start);
            result.push_back(Tokens::Token(std::stod(expr.substr(start, end).c_str())));
        
        } else if (std::isalpha(expr[start])) {
            end = expr.find_first_not_of(Tokens::LETTERS, start);
            name = expr.substr(start, end - start);

            if (Tokens::CONSTS.contains(name)) {
                result.push_back(Tokens::Token(Tokens::CONSTS.at(name)));

            } else if (Tokens::FUNCS.contains(name)) {
                args_count = Tokens::FUNCS.at(name)->args_count;
                start = expr.find_first_not_of(Tokens::WHITESPACES, end);
                closing_bracket = Validation::find_closing_bracket(expr, start);
                
                if (args_count == 1) {
                    result.push_back(Tokens::Token(Tokens::FUNCS.at(name)));
                    result.push_back(Tokens::BRACKETS.at('('));
                    tokenize(expr.substr(start + 1, closing_bracket - start - 1), result);
                    result.push_back(Tokens::BRACKETS.at(')'));
                
                } else if (args_count == 2) {
                    result.push_back(Tokens::BRACKETS.at('('));
                    tokenize(expr.substr(start + 1, expr.find_first_of(Tokens::SEPARATORS, start + 1) - start - 1), result);
                    result.push_back(Tokens::BRACKETS.at(')'));
                    
                    result.push_back(Tokens::Token(Tokens::FUNCS.at(name)));

                    result.push_back(Tokens::BRACKETS.at('('));
                    tokenize(expr.substr(expr.find_first_of(Tokens::SEPARATORS, start + 1) + 1, closing_bracket - expr.find_first_of(Tokens::SEPARATORS, start + 1) - 1), result);
                    result.push_back(Tokens::BRACKETS.at(')'));
                }
                end = closing_bracket + 1;

            } else if (name == Config::unknown_var) {
                result.push_back(Tokens::Token());
            } else {
                throw Errors::UnknownToken("expression contains an unknown token!", name);
            }

        } else if (Tokens::OPERATORS.contains(expr[start])) {
            end = start + 1;
            result.push_back(Tokens::Token(Tokens::OPERATORS.at(expr[start])));
        
        } else if (Tokens::BRACKETS.contains(expr[start])) {
            end = start + 1;
            result.push_back(Tokens::Token(Tokens::BRACKETS.at(expr[start])));
        
        } else {
            throw Errors::UnknownToken("expression contains an unknown token!", name);
        }
        
        start = expr.find_first_not_of(Tokens::WHITESPACES, end);
    }
}

void Tokenizer::print_tokens(const std::vector<Tokens::Token> &items) {
    for (const auto &item: items) {
        if (item.type == Tokens::Token::Type::NUMBER) {
            std::cout << item.value.number << ' ';
        
        } else if (item.type == Tokens::Token::Type::BRACKET) {
            std::cout << item.value.bracket->bracket << ' ';

        } else if (item.type == Tokens::Token::Type::OPERATION) {
            std::cout << item.value.operation->name << ' ';
        
        } else if (item.type == Tokens::Token::Type::UNKNOWN_VAR) {
            std::cout << Config::unknown_var << ' ';
        }
    }
}

void Tokenizer::print_tokens(const std::deque<Tokens::Token> &items) {
    for (const auto &item: items) {
        if (item.type == Tokens::Token::Type::NUMBER) {
            std::cout << item.value.number << ' ';
        
        } else if (item.type == Tokens::Token::Type::BRACKET) {
            std::cout << item.value.bracket->bracket << ' ';

        } else if (item.type == Tokens::Token::Type::OPERATION) {
            std::cout << item.value.operation->name << ' ';
        
        } else if (item.type == Tokens::Token::Type::UNKNOWN_VAR) {
            std::cout << Config::unknown_var << ' ';
        }
    }
}

void Tokenizer::print_tokens(std::stack<Tokens::Token> items) {
    while (items.size()) {
        if (items.top().type == Tokens::Token::Type::NUMBER) {
            std::cout << items.top().value.number << ' ';
        
        } else if (items.top().type == Tokens::Token::Type::BRACKET) {
            std::cout << items.top().value.bracket->bracket << ' ';

        } else if (items.top().type == Tokens::Token::Type::OPERATION) {
            std::cout << items.top().value.operation->name << ' ';
        
        } else if (items.top().type == Tokens::Token::Type::UNKNOWN_VAR) {
            std::cout << Config::unknown_var << ' ';
        }
        items.pop();
    }
}