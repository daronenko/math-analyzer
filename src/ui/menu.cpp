#include "ui/menu.h"


Ui::Option::Option(
    std::string text,
    void(*action)()
): 
    text(text)
{
    value.action = action;
    type = Type::DEFAULT;
}


Ui::Option::Option(
    std::string text, 
    Menu *menu
):
    text(text)
{
    value.menu = menu;
    type = Type::MENU;
}

Ui::Option::Option(std::string text): text(text) {
    type = Type::BACK_BUTTON;
}

void Ui::Option::exec() {
    if (type == Type::DEFAULT) {
        value.action();
    } else if (type == Type::MENU) {
        Ui::show(value.menu);
    }
}

Ui::Menu::Menu(std::string header, const std::vector<Option*> options, Type type): header(header), options(options), type(type) {}

void Ui::print_header(Menu *menu) {
    mvprintw(0, 0, menu->header.c_str(), A_BOLD);
}

void Ui::print_options(Menu *menu) {
    unsigned char row;
    for (unsigned char i {}; i < menu->options.size(); ++i) {
        if (i == menu->curr_option) {
            attron(A_REVERSE);
        }
    
        row = Ui::OPTIONS_START_ROW + i;
        if (menu->options[i]->type == Ui::Option::Type::BACK_BUTTON) {
            row += 1;
        }

        if (menu->type == Ui::Menu::Type::SETTINGS) {
            mvprintw(row, 0, (std::to_string(i + 1) + ". " + menu->options[i]->text + Config::get_str_param(menu->options[i]->text)).c_str());
        } else {
            mvprintw(row, 0, (std::to_string(i + 1) + ". " + menu->options[i]->text).c_str());
        }

        attroff(A_REVERSE);
    }
}

void Ui::process_key(Menu *menu, const int &key) {    
    switch (key) {
        case 107:  // k
        case KEY_UP:
            menu->curr_option = (menu->curr_option > 0) ? menu->curr_option - 1 : menu->options.size() - 1;
            break;
        
        case 106:  // j
        case KEY_DOWN:
            menu->curr_option = (menu->curr_option < menu->options.size() - 1) ? menu->curr_option + 1 : 0;
            break;
        
        case 10:  // enter
            if (menu->options[menu->curr_option]->type == Option::Type::BACK_BUTTON) {
                menu->back_button_pressed = true;
            } else {
                try {
                    menu->options[menu->curr_option]->exec();
                } catch (...) {}
            }
            break;
        
        case 27:  // esc
            menu->back_button_pressed = true;
            break;
    
    }
}

void Ui::setup(Menu *menu) {
    menu->back_button_pressed = false;
    menu->curr_option = 0;
}

void Ui::show(Menu *menu) {
    setup(menu);

    int key;
    while (true) {
        clear();
        print_header(menu);
        print_options(menu);
        key = getch();
        process_key(menu, key);

        if (menu->back_button_pressed) {
            Config::save_config();
            break;
        }
    }
}