#include "ScaleMenu.h"

ScaleMenu::ScaleMenu() {
    scale_scene_menu = new QMenu("Сцена");

    scale_scene_menu->addAction("Увеличить");
    scale_scene_menu->addAction("Уменьшить");
    scale_scene_menu->addAction("Сбросить");

    scale_scene_menu->actions().at(0)->setShortcut(QKeySequence("Ctrl+="));
    scale_scene_menu->actions().at(1)->setShortcut(QKeySequence("Ctrl+-"));
    scale_scene_menu->actions().at(2)->setShortcut(QKeySequence("Ctrl+0"));

    scale_font_menu = new QMenu("Текст");

    scale_font_menu->addAction("Увеличить");
    scale_font_menu->addAction("Уменьшить");
    scale_font_menu->addAction("Сбросить");

    scale_font_menu->actions().at(0)->setShortcut(QKeySequence("Ctrl+Shift+="));
    scale_font_menu->actions().at(1)->setShortcut(QKeySequence("Ctrl+Shift+-"));
    scale_font_menu->actions().at(2)->setShortcut(QKeySequence("Ctrl+Shift+0"));
}

QMenu* ScaleMenu::get_menu() {
    set_menu = new QMenu("Масштаб");

    set_menu->addAction(scale_scene_menu->menuAction());
    set_menu->addAction(scale_font_menu->menuAction());

    return set_menu;
}
QMenu* ScaleMenu::get_scale_font_menu() const {
    return scale_font_menu;
}
QMenu* ScaleMenu::get_scale_scene_menu() const {
    return scale_scene_menu;
}