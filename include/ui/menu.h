#pragma once

#include "config.h"

#include "ncurses.h"

#include <string>
#include <map>


namespace Ui {

    const static unsigned char OPTIONS_START_ROW {2};
    const static char SELECT_TAG = '*';

    struct Menu;

    struct Option {
        std::string text;

        enum class Type {
            DEFAULT,
            MENU,
            BACK_BUTTON
        } type;

        union {
            void(*action)();
            Menu *menu;
        } value;

        Option(std::string text, void(*action)());
        Option(std::string text, Menu *menu);
        Option(std::string text);

        void exec();
    };

    struct Menu {
        enum class Type {
            DEFAULT,
            SETTINGS
        } type;
        
        std::string header;
        std::vector<Option*> options;
        unsigned char curr_option {0};
        bool back_button_pressed {false};

        Menu(std::string header, const std::vector<Option*> options, Type type = Type::DEFAULT);
    };
    
    void print_header(Menu *menu);
    void print_options(Menu *menu);
    void process_key(Menu *menu, const int &key);
    
    void setup(Menu *menu);
    void show(Menu *menu);

}