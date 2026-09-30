#include "include/Buttons/OrderObjectButtons.h"

OrderObjectButtons::OrderObjectButtons() {
    common_object_buttons_name = new QGroupBox("Сцена");
    order_buttons_name = new QGroupBox("Порядок объектов на сцене");
    common_graphics_scene_name = new QGroupBox("Окно сцены");

    order_buttons.append(new QPushButton("Поворот вправо на 90°"));
    order_buttons.append(new QPushButton("Поворот влево на 90°"));
    order_buttons.append(new QPushButton("Поворот на 45°"));
    order_buttons.append(new QPushButton("Передний план"));
    order_buttons.append(new QPushButton("Задний план"));
    order_buttons.append(new QPushButton("Выше на один"));
    order_buttons.append(new QPushButton("Ниже на один"));
}
QGroupBox* OrderObjectButtons::get_common_object_buttons_name() const {
    return common_object_buttons_name;
}
QGroupBox* OrderObjectButtons::get_order_buttons_name() const {
    return order_buttons_name;
}
QGroupBox* OrderObjectButtons::get_common_graphics_scene_name() const {
    return common_graphics_scene_name;
}
QList<QPushButton*> OrderObjectButtons::get_order_buttons() const {
    return order_buttons;
}
