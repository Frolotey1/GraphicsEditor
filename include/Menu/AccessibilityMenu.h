#ifndef ACCESSIBILITYMENU_H
#define ACCESSIBILITYMENU_H
#include "QMenu"
#include "QAction"

class AccessibilityMenu {
public:
    AccessibilityMenu();
    QMenu* get_menu() const;
    QAction* get_moving_graphics_view_action() const;
private:
    QMenu* set_menu = nullptr;
    QAction* watch_only_mode_action = nullptr;
    QAction* moving_graphics_view_action = nullptr;
    QAction* sound_effects_action = nullptr;
};

#endif // ACCESSIBILITYMENU_H
