#include "include/Menu/AccessibilityMenu.h"

AccessibilityMenu::AccessibilityMenu() {
    set_menu = new QMenu("Специальные возможности");

    watch_only_mode_action = new QAction("Режим просмотра");
    watch_only_mode_action->setCheckable(true);
    watch_only_mode_action->setChecked(false);

    moving_graphics_view_action = new QAction("Панорамирование сцены");
    moving_graphics_view_action->setCheckable(true);
    moving_graphics_view_action->setChecked(false);

    sound_effects_action = new QAction("Звуковые эффекты");
    sound_effects_action->setCheckable(true);
    sound_effects_action->setChecked(true);

    set_menu->addAction(watch_only_mode_action);
    set_menu->addAction(moving_graphics_view_action);
    set_menu->addAction(sound_effects_action);
}

QMenu* AccessibilityMenu::get_menu() const {
    return set_menu;
}
QAction* AccessibilityMenu::get_moving_graphics_view_action() const {
    return moving_graphics_view_action;
}
