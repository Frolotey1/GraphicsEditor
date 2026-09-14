#include "ReferenceMenu.h"

QMenu* ReferenceMenu::get_menu() {
    QMenu* set_menu = new QMenu("Справка");

    set_menu->addAction(new QAction("О программе"));

    return set_menu;
}
