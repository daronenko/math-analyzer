#pragma once

#include "shunting_yard/tokens.h"
#include "shunting_yard/tokenizer.h"

#include <vector>
#include <deque>
#include <stack>


namespace Algo {
    
    namespace Errors {

        class AlgoError {
          public: 
            AlgoError(std::string_view message): message(message) {}
            std::string_view get_msg() const { return message; }
        
          protected:
            std::string_view message;
        };

        class DomainError: public AlgoError {
          public:
            const Tokens::Operation *operation;
            const std::vector<double> args;

            DomainError(
                std::string_view message,
                std::vector<double> args,
                const Tokens::Operation *operation
            ): 
                AlgoError(message),
                args(args),
                operation(operation)
            {}
        };

    }

    std::deque<Tokens::Token> shunting_yard(const std::vector<Tokens::Token> &tokens);
    std::deque<Tokens::Token> shunting_yard(const std::string expr);
    double compute(const std::deque<Tokens::Token> &postfix_tokens, const double var_value);
    double eval(std::string expr, const double var_value);

}