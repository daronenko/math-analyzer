#include "shunting_yard/tokens.h"


const unsigned char Tokens::MAX_ARGS_COUNT {2};

std::string_view Tokens::OPENING_BRACKETS {"([{"};
std::string_view Tokens::CLOSING_BRACKETS {")]}"};
std::string_view Tokens::WHITESPACES {" \t"};
std::string_view Tokens::SEPARATORS {",;"};
std::string_view Tokens::LETTERS {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
std::string_view Tokens::DIGIT_TOKENS {".0123456789"};

const std::unordered_map<char, Tokens::Operation*> Tokens::OPERATORS({
    {
        '+',
        new Operation(
            "+",
            2,
            10,
            [](std::vector<double> &args) {
                return args[1] + args[0];
            }
        )
    },
    {
        '-',
        new Operation(
            "-",
            2,
            10,
            [](std::vector<double> &args) {
                return args[1] - args[0];
            }
        )
    },
    {
        '*',
        new Operation(
            "*",
            2,
            20,
            [](std::vector<double> &args) {
                return args[1] * args[0];
            }
        )
    },
    {
        '/',
        new Operation(
            "/",
            2,
            20,
            [](std::vector<double> &args) {
                return args[1] / args[0];
            }
        )
    },
    {
        '^',
        new Operation(
            "^",
            2,
            30,
            [](std::vector<double> &args) {
                return std::pow(args[1], args[0]);
            }
        )
    },
});

const std::unordered_map<std::string_view, Tokens::Operation*> Tokens::FUNCS({
    {
        "sin",
        new Operation(
            "sin",
            1,
            40,
            [](std::vector<double> &args) {
                return std::sin(args[0]);
            }
        )
    },
    {
        "arcsin",
        new Operation(
            "arcsin",
            1,
            40,
            [](std::vector<double> &args) {
                return std::asin(args[0]);
            }
        )
    },
    {
        "cos",
        new Operation(
            "cos",
            1,
            40,
            [](std::vector<double> &args) {
                return std::cos(args[0]);
            }
        )
    },
    {
        "arccos",
        new Operation(
            "arccos",
            1,
            1,
            [](std::vector<double> &args) {
                return std::acos(args[0]);
            }
        )
    },
    {
        "tg",
        new Operation(
            "tg",
            1,
            1,
            [](std::vector<double> &args) {
                return std::tan(args[0]);
            }
        )
    },
    {
        "arctg",
        new Operation(
            "arctg",
            1,
            40,
            [](std::vector<double> &args) {
                return std::atan(args[0]);
            }
        )
    },
    {
        "ctg",
        new Operation(
            "ctg",
            1,
            40,
            [](std::vector<double> &args) {
                return 1 / std::tan(args[0]);
            }
        )
    },
    {
        "arcctg",
        new Operation(
            "arcctg",
            1,
            40,
            [](std::vector<double> &args) {
                return std::atan(1 / args[0]);
            }
        )
    },
    {
        "log",
        new Operation(
            "log",
            2,
            40,
            [](std::vector<double> &args) {
                return std::log(args[0]) / std::log(args[1]);
            }
        )
    },
    {
        "ln",
        new Operation(
            "ln",
            1,
            40,
            [](std::vector<double> &args) {
                return std::log(args[0]);
            }
        )
    },
    {
        "abs",
        new Operation(
            "abs",
            1,
            40,
            [](std::vector<double> &args) {
                return std::abs(args[0]);
            }
        )
    },
    {
        "pow",
        new Operation(
            "pow",
            2,
            40,
            [](std::vector<double> &args) {
                return std::pow(args[1], args[0]);
            }
        )
    },
    {
        "sqrt",
        new Operation(
            "sqrt",
            1,
            40,
            [](std::vector<double> &args) {
                return std::sqrt(args[0]);
            }
        )
    }
});

const std::unordered_map<char, Tokens::Bracket*> Tokens::BRACKETS({
    {
        '(',
        new Bracket(
            Bracket::Type::OPENING,
            '(',
            ')'
        )
    },
    {
        ')',
        new Bracket(
            Bracket::Type::CLOSING,
            ')',
            '('
        )
    },
    {
        '[',
        new Bracket(
            Bracket::Type::OPENING,
            '[',
            ']'
        )
    },
    {
        ']',
        new Bracket(
            Bracket::Type::CLOSING,
            ']',
            '['
        )
    },
    {
        '{',
        new Bracket(
            Bracket::Type::OPENING,
            '{',
            '}'
        )
    },
    {
        '}',
        new Bracket(
            Bracket::Type::CLOSING,
            '}',
            '{'
        )
    }
});

const std::unordered_map<std::string_view, const double> Tokens::CONSTS({
    {"pi", M_PI},
    {"e", M_E}
});

Tokens::Operation::Operation(
    std::string_view name,
    const unsigned char args_count,
    const unsigned char priority,
    double(*exec)(std::vector<double>&)
): 
    name(name),
    args_count(args_count),
    priority(priority),
    exec(exec)
{}

Tokens::Bracket::Bracket(
    Type type,
    const char bracket,
    const char matching
):
    type(type),
    bracket(bracket),
    matching(matching)
{}

Tokens::Token::Token() {
    type = Type::UNKNOWN_VAR;
}

Tokens::Token::Token(double number) {
    type = Type::NUMBER;
    value.number = number;
}

Tokens::Token::Token(const Operation *operation) {
    type = Type::OPERATION;
    value.operation = operation;
}

Tokens::Token::Token(const Bracket *bracket) {
    type = Type::BRACKET;
    value.bracket = bracket;
}
