#include "ObjectSettingsLists.h"

ObjectSettingsLists::ObjectSettingsLists() {
    list_circuit_items["Красный"] = "red";
    list_circuit_items["Зеленый"] = "green";
    list_circuit_items["Синий"] = "blue";
    list_circuit_items["Желтый"] = "yellow";
    list_circuit_items["Черный"] = "black";
    list_circuit_items["Белый"] = "white";
    list_circuit_items["Создать свой цвет"] = "Создать свой цвет";

    list_brush_items["Красный"] = "red";
    list_brush_items["Зеленый"] = "green";
    list_brush_items["Синий"] = "blue";
    list_brush_items["Желтый"] = "yellow";
    list_brush_items["Черный"] = "black";
    list_brush_items["Белый"] = "white";
    list_brush_items["Создать свой цвет"] = "Создать свой цвет";

    list_color_window_items["Красный"] = "red";
    list_color_window_items["Зеленый"] = "green";
    list_color_window_items["Синий"] = "blue";
    list_color_window_items["Желтый"] = "yellow";
    list_color_window_items["Черный"] = "black";
    list_color_window_items["Белый"] = "white";
    list_color_window_items["Создать свой цвет"] = "Создать свой цвет";

    list_text_font_items["Adwaita Sans"] = "Adwaita Sans";
    list_text_font_items["Adwaita Mono"] = "Adwaita Mono";
    list_text_font_items["Comfortaa"] = "Comfortaa";
    list_text_font_items["Liberation Mono"] = "Liberation Mono";
    list_text_font_items["Cantarell Light"] = "Cantarell Light";
    list_text_font_items["Cantarell Thin"] = "Cantarell Thin";
    list_text_font_items["Создать свой шрифт"] = "Создать свой шрифт";
}

QString ObjectSettingsLists::get_circuit(QString current_item) const {
    return list_circuit_items[current_item];
}
QString ObjectSettingsLists::get_brush(QString current_item) const {
    return list_brush_items[current_item];
}
QString ObjectSettingsLists::get_color_window(QString current_item) const {
    return list_color_window_items[current_item];
}
QString ObjectSettingsLists::get_text_font(QString current_item) const {
    return list_text_font_items[current_item];
}
