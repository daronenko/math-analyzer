#include "shunting_yard/algo.h"


std::deque<Tokens::Token> Algo::shunting_yard(const std::vector<Tokens::Token> &tokens) {
    std::deque<Tokens::Token> result;
    std::stack<Tokens::Token> stack;

    for (const auto &item: tokens) {
        if (item.type == Tokens::Token::Type::NUMBER || item.type == Tokens::Token::Type::UNKNOWN_VAR) {
            result.push_back(item);
        
        } else if (item.type == Tokens::Token::Type::OPERATION) {
            while (
                stack.size() &&
                stack.top().value.operation->priority >= item.value.operation->priority &&
                stack.top().type != Tokens::Token::Type::BRACKET
            ) {
                result.push_back(stack.top());
                stack.pop();
            }
            stack.push(item);
        
        } else if (item.type == Tokens::Token::Type::BRACKET) {
            if (item.value.bracket->type == Tokens::Bracket::Type::OPENING) {
                stack.push(item);
            } else {
                while (stack.top().value.bracket->type != Tokens::Bracket::Type::OPENING) {
                    result.push_back(stack.top());
                    stack.pop();
                }
                stack.pop();
            }
        }
    }

    while (stack.size()) {
        result.push_back(stack.top());
        stack.pop();
    }

    return result;
}

std::deque<Tokens::Token> Algo::shunting_yard(const std::string expr) {
    std::vector<Tokens::Token> result;
    Tokenizer::tokenize(expr, result);
    
    std::deque<Tokens::Token> postfix {Algo::shunting_yard(result)};
    
    return postfix;
}

double Algo::compute(const std::deque<Tokens::Token> &postfix_tokens, const double var_value) {
    std::stack<Tokens::Token> stack;

    Tokens::Token operand_1, operand_2;
    for (const auto &item: postfix_tokens) {
        if (item.type == Tokens::Token::Type::NUMBER) {
            stack.push(item);
        
        } else if (item.type == Tokens::Token::Type::UNKNOWN_VAR) {
            stack.push(Tokens::Token(var_value));
        
        } else {
            std::vector<double> args;
            
            for (unsigned char i {}; i < item.value.operation->args_count; ++i) {
                args.push_back(stack.top().value.number);
                stack.pop();
            }

            try {
                stack.push(Tokens::Token(item.value.operation->exec(args)));
            } catch (const char* err_msg) {
                throw Errors::DomainError("at least one of the args is not a domain!", args, item.value.operation);
            }
        }
    }
    
    return stack.top().value.number;
}

double Algo::eval(std::string expr, const double var_value) {
    std::vector<Tokens::Token> result;
    Tokenizer::tokenize(expr, result);
    
    std::deque<Tokens::Token> postfix {Algo::shunting_yard(result)};
    
    return Algo::compute(postfix, var_value);
}