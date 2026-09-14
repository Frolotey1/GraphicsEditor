#include "CommonSettingsMenu.h"

QMenu* CommonSettingsMenu::get_menu() {
    set_menu = new QMenu("Настройки");

    window_action = new QAction("Оформление окна");
    window_action->setShortcut(QKeySequence("Ctrl+W"));

    font_action = new QAction("Настройка шрифтов текста");
    font_action->setShortcut(QKeySequence("Ctrl+S"));

    reset_action = new QAction("Возвращение по умолчанию");
    reset_action->setShortcut(QKeySequence("Ctrl+Z"));

    set_menu->addAction(window_action);
    set_menu->addSeparator();
    set_menu->addAction(font_action);
    set_menu->addSeparator();
    set_menu->addAction(reset_action);

    return set_menu;
}

QAction* CommonSettingsMenu::get_window_action() const {return window_action;}
QAction* CommonSettingsMenu::get_font_action() const {return font_action;}
QAction* CommonSettingsMenu::get_reset_action() const {return reset_action;}