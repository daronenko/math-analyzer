#include "ui/actions.h"


void Actions::find_extremes() {
    const std::vector<double> extremes = Analysis::get_extremes(
        Config::postfix_func_tokens,
        Config::interval_start,
        Config::interval_end,
        Config::accuracy
    );

    print_result("Extremes", extremes);
}

void Actions::find_root() {
    const double root {Analysis::get_root(
        Config::postfix_func_tokens,
        Config::interval_start,
        Config::interval_end,
        Config::accuracy
    )};

    print_result("Root", root);
}

void Actions::find_integral() {
    const double integral {Analysis::get_integral(
        Config::postfix_func_tokens,
        Config::interval_start,
        Config::interval_end,
        Config::accuracy
    )};

    print_result("Integral", integral);
}

void Actions::print_result(const std::string name, const double result) {
    endwin();
    system("clear");
    
    printf("%s: %.4lf", name.c_str(), result);

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    getch();
}

void Actions::print_result(const std::string name, const std::vector<double> result) {
    endwin();
    system("clear");

    printf("%s: ", name.c_str());
    for (const auto &item: result) {
        printf("%.4lf ", item);
    }

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    getch();
}