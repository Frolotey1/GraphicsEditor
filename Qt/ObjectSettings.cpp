#include "ObjectSettings.h"

ObjectSettings::ObjectSettings() {
    object_combobox_name = new QGroupBox("Фигуры");
    circuit_combobox_name = new QGroupBox("Цвет контура");
    brush_combobox_name = new QGroupBox("Цвет заливки");
    common_combobox_name = new QGroupBox("Настройки графического окна");
}

QComboBox* ObjectSettings::get_object_combobox() {
    object_combobox = new QComboBox(object_combobox_name);

    object_combobox->addItems({"Прямоугольник",
                            "Эллипс",
                            "Линия",
                            "Текст",
                            "Многоугольник",
                            "Создать свой объект"});

    return object_combobox;
}

QComboBox* ObjectSettings::get_circuit_combobox() {
    circuit_combobox = new QComboBox(circuit_combobox_name);

    circuit_combobox->addItems({"red",
                                "green",
                                "blue",
                                "yellow",
                                "black",
                                "white",
                                "Создать свой цвет"});

    return circuit_combobox;
}
QComboBox* ObjectSettings::get_brush_combobox() {
    brush_combobox = new QComboBox(brush_combobox_name);

    brush_combobox->addItems({"red",
                              "green",
                              "blue",
                              "yellow",
                              "black",
                              "white",
                              "Создать свой цвет"});

    return brush_combobox;
}
QGroupBox* ObjectSettings::get_object_combobox_name() {
    return object_combobox_name;
}
QGroupBox* ObjectSettings::get_circuit_combobox_name() {
    return circuit_combobox_name;
}
QGroupBox* ObjectSettings::get_brush_combobox_name() {
    return brush_combobox_name;
}
QGroupBox* ObjectSettings::get_common_combobox_name() {
    return common_combobox_name;
}
