#include "include/Settings/ObjectSettings.h"

ObjectSettings::ObjectSettings() {
    configure_object_combobox_name = new QGroupBox("Фигуры");
    configure_circuit_combobox_name = new QGroupBox("Цвет контура");
    configure_brush_combobox_name = new QGroupBox("Цвет заливки");
    configure_color_window_name = new QGroupBox("Цвет окна");
    configure_text_font_name = new QGroupBox("Шрифт текста");
    common_combobox_name = new QGroupBox("Настройки сцены");

    configure_object_combobox = new QComboBox(configure_object_combobox_name);

    configure_object_combobox->addItems({
        "Прямоугольник",
        "Эллипс",
        "Линия",
        "Текст",
        "Многоугольник",
        "Создать свой объект"
    });

    configure_circuit_combobox = new QComboBox(configure_circuit_combobox_name);

    configure_circuit_combobox->addItems({
        "Красный",
        "Зеленый",
        "Синий",
        "Желтый",
        "Черный",
        "Белый",
        "Создать свой цвет"
    });

    configure_brush_combobox = new QComboBox(configure_brush_combobox_name);

    configure_brush_combobox->addItems({
        "Красный",
        "Зеленый",
        "Синий",
        "Желтый",
        "Черный",
        "Белый",
        "Создать свой цвет"
    });

    configure_color_window_combobox = new QComboBox(configure_color_window_name);

    configure_color_window_combobox->addItems({
        "Красный",
        "Зеленый",
        "Синий",
        "Желтый",
        "Черный",
        "Белый",
        "Создать свой цвет"
    });

    configure_text_font_combobox = new QComboBox(configure_text_font_name);

    configure_text_font_combobox->addItems({
        "Adwaita Sans",
        "Adwaita Mono",
        "Comfortaa",
        "Liberation Mono",
        "Cantarell Light",
        "Cantarell Thin",
        "Создать свой шрифт"
    });
}

QComboBox* ObjectSettings::get_configure_object_combobox() const {
    return configure_object_combobox;
}
QComboBox* ObjectSettings::get_configure_circuit_combobox() const {
    return configure_circuit_combobox;
}
QComboBox* ObjectSettings::get_configure_brush_combobox() const {
    return configure_brush_combobox;
}
QComboBox* ObjectSettings::get_configure_text_font_combobox() const {
    return configure_text_font_combobox;
}
QComboBox* ObjectSettings::get_configure_color_window_combobox() const {
    return configure_color_window_combobox;
}
QGroupBox* ObjectSettings::get_configure_object_combobox_name() const {
    return configure_object_combobox_name;
}
QGroupBox* ObjectSettings::get_configure_circuit_combobox_name() const {
    return configure_circuit_combobox_name;
}
QGroupBox* ObjectSettings::get_configure_brush_combobox_name() const {
    return configure_brush_combobox_name;
}
QGroupBox* ObjectSettings::get_configure_color_window_name() const {
    return configure_color_window_name;
}
QGroupBox* ObjectSettings::get_configure_text_font_name() const {
    return configure_text_font_name;
}
QGroupBox* ObjectSettings::get_common_combobox_name() const {
    return common_combobox_name;
}
