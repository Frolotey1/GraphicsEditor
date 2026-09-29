#ifndef OBJECTSETTINGSLISTS_H
#define OBJECTSETTINGSLISTS_H
#include "QMap"
#include "QString"

class ObjectSettingsLists {
public:
    ObjectSettingsLists();

    QString get_circuit(QString current_item) const;
    QString get_brush(QString current_item) const;
    QString get_color_window(QString current_item) const;
    QString get_text_font(QString current_item) const;
private:
    QMap<QString,QString> list_circuit_items;
    QMap<QString,QString> list_brush_items;
    QMap<QString,QString> list_color_window_items;
    QMap<QString,QString> list_text_font_items;
};

#endif // OBJECTSETTINGSLISTS_H
