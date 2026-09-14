#ifndef VIEWWINDOWMENU_H
#define VIEWWINDOWMENU_H
#include "QMenu"
#include "QAction"
#include "QString"

class ViewWindowMenu {
    QMenu* set_menu;
    QAction* fullscreen_action;
    QAction* normalscreen_action;
    QAction* reset_grid_action;
    QMenu* scale_scene_menu;
    QMenu* scale_font_menu;
    QMenu* grid_menu;
public:
    ViewWindowMenu();
    QMenu* get_menu();

    QMenu* get_scale_font_menu() const;
    QMenu* get_scale_scene_menu() const;
    QMenu* get_grid_menu() const;
    QAction* get_fullscreen_action() const;
    QAction* get_normalscreen_action() const;
    QAction* get_reset_grid_action() const;
};

#endif // VIEWWINDOWMENU_H
