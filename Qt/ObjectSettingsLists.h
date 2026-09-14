#ifndef OBJECTSETTINGSLISTS_H
#define OBJECTSETTINGSLISTS_H
#include "QList"
#include "QString"
#include "QComboBox"
#include "ObjectSettings.h"

class ObjectSettingsLists : public ObjectSettings {
    QComboBox* object_combobox;
    QComboBox* circuit_combobox;
    QComboBox* brush_combobox;

    QList<QString> list_object_items;
    QList<QString> list_circuit_items;
    QList<QString> list_brush_items;
public:
    ObjectSettingsLists() {
        object_combobox = get_object_combobox();
        circuit_combobox = get_circuit_combobox();
        brush_combobox = get_brush_combobox();

        list_object_items.reserve(object_combobox->count());
        list_circuit_items.reserve(circuit_combobox->count());
        list_brush_items.reserve(brush_combobox->count());
    }
    QString get_object(int current_index);
    QString get_circuit(int current_index);
    QString get_brush(int current_index);
};

#endif // OBJECTSETTINGSLISTS_H
