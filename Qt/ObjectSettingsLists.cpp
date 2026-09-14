#include "ObjectSettingsLists.h"

QString ObjectSettingsLists::get_object(int current_index) {
    if(current_index == -1) return QString("");

    for(int i = 0; i < object_combobox->count(); ++i) {
        list_object_items.append(object_combobox->itemText(i));
    }

    return list_object_items.at(current_index);
}
QString ObjectSettingsLists::get_circuit(int current_index) {
    if(current_index == -1) return QString("");

    for(int i = 0; i < circuit_combobox->count(); ++i) {
        list_circuit_items.append(circuit_combobox->itemText(i));
    }

    return list_circuit_items.at(current_index);
}
QString ObjectSettingsLists::get_brush(int current_index) {
    if(current_index == -1) return QString("");

    for(int i = 0; i < brush_combobox->count(); ++i) {
        list_brush_items.append(brush_combobox->itemText(i));
    }

    return list_brush_items.at(current_index);
}
