#ifndef WINDOWTHEMEMANAGER_H
#define WINDOWTHEMEMANAGER_H
#include "QPalette"
#include "QMap"
#include "QList"
#include "QPair"
#include "QColor"
#include "QPalette"
#include "QString"

class WindowThemeManager {
public:
    WindowThemeManager(QString type_style);
    QPair<QPair<QColor,QColor>,QPair<QColor,QColor>> get_style_palette();
private:
    QMap<QString,QList<QPair<QColor,QColor>>> theme_type_styles;
    QPalette tool_bar_palette;
    QPalette window_palette;
    QString set_type_style;
};

#endif // WINDOWTHEMEMANAGER_H
