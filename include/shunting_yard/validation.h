#pragma once

#include "shunting_yard/tokens.h"
#include "config.h"

#include <string_view>
#include <stack>


namespace Validation {

    namespace Errors {

        class ValidationError {
          public: 
            ValidationError(std::string_view message): message(message) {}
            std::string_view get_msg() const { return message; }
        
          protected:
            std::string_view message;
        };

        class BracketsSequenceOrderError: public ValidationError {
          public: 
            BracketsSequenceOrderError(std::string_view message): ValidationError(message) {}
        };

        class OperatorsOrderError: public ValidationError {
          public: 
            OperatorsOrderError(std::string_view message): ValidationError(message) {}
        };

        class FunctionsFormatError: public ValidationError {
          public: 
            FunctionsFormatError(std::string_view message): ValidationError(message) {}
        };

        class AlphabetError: public ValidationError {
          public: 
            AlphabetError(std::string_view message): ValidationError(message) {}
        };

        class UnknownFunctionError: public ValidationError {
          public: 
            UnknownFunctionError(std::string_view message): ValidationError(message) {}
        };

        class FunctionArgsNumberError: public ValidationError {
          public: 
            FunctionArgsNumberError(std::string_view message): ValidationError(message) {}
        };

        class UnknownVariableError: public ValidationError {
          public: 
            UnknownVariableError(std::string_view message): ValidationError(message) {}
        };

        class InvalidVariableFormatError: public ValidationError {
          public: 
            InvalidVariableFormatError(std::string_view message): ValidationError(message) {}
        };

    }

    void validate_alphabet(std::string_view expr);
    void validate_brackets(std::string_view expr);
    void validate_tokens_order(std::string_view expr);
    
    size_t find_closing_bracket(std::string_view expr, size_t opening_bracket);
    void validate_function(std::string_view expr);
    void validate_var(std::string_view expr);
    void validate_letter_combos(std::string_view expr);

    void validate_var_format(std::string_view expr);
}