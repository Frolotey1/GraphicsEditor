#include "ViewWindowMenu.h"

ViewWindowMenu::ViewWindowMenu() {
    scale_scene_menu = new QMenu("Масштаб сцены");

    scale_scene_menu->addAction("Увеличить");
    scale_scene_menu->addAction("Уменьшить");
    scale_scene_menu->addAction("Сбросить");

    scale_scene_menu->actions().at(0)->setShortcut(QKeySequence("Ctrl+="));
    scale_scene_menu->actions().at(1)->setShortcut(QKeySequence("Ctrl+-"));
    scale_scene_menu->actions().at(2)->setShortcut(QKeySequence("Ctrl+0"));

    scale_font_menu = new QMenu("Масштаб текста");

    scale_font_menu->addAction("Увеличить");
    scale_font_menu->addAction("Уменьшить");
    scale_font_menu->addAction("Сбросить");

    scale_font_menu->actions().at(0)->setShortcut(QKeySequence("Ctrl+Shift+="));
    scale_font_menu->actions().at(1)->setShortcut(QKeySequence("Ctrl+Shift+-"));
    scale_font_menu->actions().at(2)->setShortcut(QKeySequence("Ctrl+Shift+0"));

    grid_menu = new QMenu("Показать сетку");

    for(int grid_size = 10; grid_size < 60; grid_size += 10) {
        grid_menu->addAction(QString("%1px").arg(grid_size));
    }

    grid_menu->addAction("Задать свой размер сетки");

}

QMenu* ViewWindowMenu::get_menu() {
    set_menu = new QMenu("Вид");

    fullscreen_action = new QAction("Полноэкранный режим");
    normalscreen_action = new QAction("Нормальный режим");
    reset_grid_action = new QAction("Сбросить сетку");

    set_menu->addAction(fullscreen_action);
    set_menu->addSeparator();
    set_menu->addAction(normalscreen_action);
    set_menu->addSeparator();
    set_menu->addAction(grid_menu->menuAction());
    set_menu->addSeparator();
    set_menu->addAction(reset_grid_action);
    set_menu->addSeparator();
    set_menu->addAction(scale_scene_menu->menuAction());
    set_menu->addSeparator();
    set_menu->addAction(scale_font_menu->menuAction());

    return set_menu;
}
QMenu* ViewWindowMenu::get_scale_font_menu() const {
    return scale_font_menu;
}
QMenu* ViewWindowMenu::get_scale_scene_menu() const {
    return scale_scene_menu;
}
QMenu* ViewWindowMenu::get_grid_menu() const {
    return grid_menu;
}
QAction* ViewWindowMenu::get_fullscreen_action() const {
    return fullscreen_action;
}
QAction* ViewWindowMenu::get_normalscreen_action() const {
    return normalscreen_action;
}
QAction* ViewWindowMenu::get_reset_grid_action() const {
    return reset_grid_action;
}