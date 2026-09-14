#ifndef OBJECTSETTINGS_H
#define OBJECTSETTINGS_H
#include "QGroupBox"
#include "QComboBox"
#include "QString"

class ObjectSettings {
    QGroupBox* object_combobox_name;
    QGroupBox* circuit_combobox_name;
    QGroupBox* brush_combobox_name;
    QGroupBox* common_combobox_name;
    QComboBox* object_combobox;
    QComboBox* circuit_combobox;
    QComboBox* brush_combobox;
public:
    ObjectSettings();
    QComboBox* get_object_combobox();
    QComboBox* get_circuit_combobox();
    QComboBox* get_brush_combobox();

    QGroupBox* get_object_combobox_name();
    QGroupBox* get_circuit_combobox_name();
    QGroupBox* get_brush_combobox_name();
    QGroupBox* get_common_combobox_name();
};

#endif // OBJECTSETTINGS_H
