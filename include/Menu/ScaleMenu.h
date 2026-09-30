#ifndef SCALEMENU_H
#define SCALEMENU_H
#include "QMenu"
#include "QAction"
#include "QString"

class ScaleMenu {
    QMenu* set_menu;
    QMenu* scale_scene_menu;
    QMenu* scale_font_menu;
public:
    ScaleMenu();
    QMenu* get_menu();
    QMenu* get_scale_font_menu() const;
    QMenu* get_scale_scene_menu() const;
};

#endif // SCALEMENU_H
