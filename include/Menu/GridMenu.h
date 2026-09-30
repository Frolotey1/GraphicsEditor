#ifndef GRIDMENU_H
#define GRIDMENU_H
#include "QMenu"
#include "QAction"

class GridMenu {
public:
    GridMenu();
    QMenu* get_grid_menu() const;
private:
    QMenu* set_grid_menu = nullptr;
    QAction* reset_grid_action = nullptr;
};

#endif // GRIDMENU_H
