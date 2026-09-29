#ifndef OBJECTSETTINGS_H
#define OBJECTSETTINGS_H
#include "QGroupBox"
#include "QComboBox"
#include "QAction"
#include "QString"

class ObjectSettings {
public:
    ObjectSettings();
    QComboBox* get_configure_object_combobox() const;
    QComboBox* get_configure_circuit_combobox() const;
    QComboBox* get_configure_brush_combobox() const;
    QComboBox* get_configure_color_window_combobox() const;
    QComboBox* get_configure_text_font_combobox() const;
    QComboBox* get_configure_graphics_combobox() const;

    QGroupBox* get_configure_object_combobox_name() const;
    QGroupBox* get_configure_circuit_combobox_name() const;
    QGroupBox* get_configure_brush_combobox_name() const;
    QGroupBox* get_configure_color_window_name() const;
    QGroupBox* get_configure_text_font_name() const;
    QGroupBox* get_common_combobox_name() const;
private:
    QGroupBox* configure_object_combobox_name = nullptr;
    QGroupBox* configure_circuit_combobox_name = nullptr;
    QGroupBox* configure_brush_combobox_name = nullptr;
    QGroupBox* configure_color_window_name = nullptr;
    QGroupBox* configure_text_font_name = nullptr;
    QGroupBox* common_combobox_name = nullptr;
    QComboBox* configure_object_combobox = nullptr;
    QComboBox* configure_circuit_combobox = nullptr;
    QComboBox* configure_brush_combobox = nullptr;
    QComboBox* configure_color_window_combobox = nullptr;
    QComboBox* configure_text_font_combobox = nullptr;
};

#endif // OBJECTSETTINGS_H
