#pragma once

#include "shunting_yard/tokens.h"
#include "config.h"

#include <vector>
#include <deque>
#include <stack>
#include <iostream>


namespace Tokenizer {

    namespace Errors {

        class TokenizerError {
          public: 
            TokenizerError(std::string_view message): message(message) {}
            std::string_view get_msg() const { return message; }
        
          protected:
            std::string_view message;
        };

        class UnknownToken: public TokenizerError {
          public:
            std::string_view name;

            UnknownToken(
                std::string_view message,
                std::string_view name
            ): 
                TokenizerError(message),
                name(name)
            {}
        };

    }

    void tokenize(std::string expr, std::vector<Tokens::Token> &result);
    
    void print_tokens(const std::vector<Tokens::Token> &items);
    void print_tokens(const std::deque<Tokens::Token> &items);
    void print_tokens(std::stack<Tokens::Token> items);

}