#include "ui/menu.h"
#include "ui/actions.h"
#include "config.h"


int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);

    const std::vector<Ui::Option*> settings_options {
        new Ui::Option("ARGUMENT", []{ endwin(); Config::set_arg(Config::get_string(Config::ARGUMENT_NAME)); }),
        new Ui::Option("FUNCTION", []{ endwin(); Config::set_func(Config::get_string(Config::FUNCTION_NAME)); }),
        new Ui::Option("INTERVAL", []{ endwin(); Config::set_interval(Config::get_double("START"), Config::get_double("END")); }),
        new Ui::Option("ACCURACY", []{ endwin(); Config::set_accuracy(Config::get_double(Config::ACCURACY_NAME)); }),
        new Ui::Option("Back")
    };
    
    Ui::Menu settings("Settings", settings_options, Ui::Menu::Type::SETTINGS);

    const std::vector<Ui::Option*> options {
        new Ui::Option("Find extremes", []{ Actions::find_extremes(); }),
        new Ui::Option("Find root", []{ Actions::find_root(); }),
        new Ui::Option("Find integral", []{ Actions::find_integral(); }),
        new Ui::Option("Settings", &settings),
        new Ui::Option("Exit")
    };

    Ui::Menu menu("Math Analyzer", options);
    std::cout << "___________________" << std::endl;
    Config::load_config();
    std::cout << "___________________" << std::endl;
    Ui::show(&menu);

    endwin();
    system("clear");

    return 0;
}
