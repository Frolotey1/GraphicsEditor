#include "include/Menu/CommonSettingsMenu.h"

CommonSettingsMenu::CommonSettingsMenu() {
    style_menu = new QMenu("Вид приложения");

    QStringList available_styles = QStyleFactory::keys();

    for(auto& style : available_styles) {
        style_menu->addAction(style);
    }

    design_window_menu = new QMenu("Оформление окна");

    design_window_menu->addAction("Светлая тема");
    design_window_menu->addAction("Темная тема");
    design_window_menu->addAction("Светло-темная тема");
    design_window_menu->addAction("Темно-светлая тема");

    configure_text_font_action = new QAction("Настройка шрифта");
    configure_text_font_action->setShortcut(QKeySequence("Ctrl+Alt+S"));

    return_all_default_action = new QAction("Возврат по умолчанию");
    return_all_default_action->setShortcut(QKeySequence("Ctrl+Alt+Z"));

    theme_style_lists["Светлая тема"] = {qMakePair("white","black"),qMakePair("white","black")};
    theme_style_lists["Темная тема"] = {qMakePair("black","white"),qMakePair("black","white")};
    theme_style_lists["Светло-темная тема"] = {qMakePair("white","black"),qMakePair("black","white")};
    theme_style_lists["Темно-светлая тема"] = {qMakePair("black","white"),qMakePair("white","black")};
}

QMenu* CommonSettingsMenu::get_menu() {
    set_menu = new QMenu("Настройки");

    set_menu->addMenu(style_menu);
    set_menu->addMenu(design_window_menu);
    set_menu->addAction(configure_text_font_action);
    set_menu->addAction(return_all_default_action);

    return set_menu;
}
QMap<QString,QList<QPair<QString,QString>>> CommonSettingsMenu::get_theme_style_lists() const {
    return theme_style_lists;
}