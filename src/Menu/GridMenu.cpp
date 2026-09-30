#include "include/Menu/GridMenu.h"

GridMenu::GridMenu() {
    set_grid_menu = new QMenu("Сетка");

    for(int grid_size = 10; grid_size < 60; grid_size += 10) {
        set_grid_menu->addAction(QString("%1px").arg(grid_size));
    }

    reset_grid_action = new QAction("Сбросить сетку");

    set_grid_menu->addAction(reset_grid_action);
}
QMenu* GridMenu::get_grid_menu() const {
    return set_grid_menu;
}
