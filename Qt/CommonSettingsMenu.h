#ifndef COMMONSETTINGSMENU_H
#define COMMONSETTINGSMENU_H
#include "QMenu"
#include "QAction"
#include "QString"

class CommonSettingsMenu {
    QMenu* set_menu;
    QAction* window_action;
    QAction* smooth_action;
    QAction* font_action;
    QAction* reset_action;
public:
    QMenu* get_menu();

    QAction* get_window_action() const;
    QAction* get_font_action() const;
    QAction* get_reset_action() const;
};

#endif // COMMONSETTINGSMENU_H
