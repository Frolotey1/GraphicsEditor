#ifndef COMMONSETTINGSMENU_H
#define COMMONSETTINGSMENU_H
#include "QMenu"
#include "QAction"
#include "QStringList"
#include "QStyleFactory"
#include "QList"
#include "QMap"
#include "QPair"
#include "QString"

class CommonSettingsMenu {
public:
    CommonSettingsMenu();
    QMenu* get_menu();
    QMap<QString,QList<QPair<QString,QString>>> get_theme_style_lists() const;
private:
    QMenu* set_menu = nullptr;
    QMenu* design_window_menu = nullptr;
    QMenu* style_menu = nullptr;
    QAction* configure_text_font_action = nullptr;
    QAction* return_all_default_action = nullptr;

    QMap<QString,QList<QPair<QString,QString>>> theme_style_lists;
};

#endif // COMMONSETTINGSMENU_H
