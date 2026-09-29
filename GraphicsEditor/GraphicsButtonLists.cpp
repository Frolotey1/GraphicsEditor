#include "GraphicsButtonLists.h"

GraphicsButtonLists::GraphicsButtonLists() {
    common_button_name = new QGroupBox("Действия над объектами");

    add_figure_button = new QPushButton("Добавить объект");
    remove_all_figures_button = new QPushButton("Удалить все объекты");
    remove_button = new QPushButton("Удалить объект");
    end_drawing_button = new QPushButton("Закончить рисование объекта");
}

QGroupBox* GraphicsButtonLists::get_common_button_name() const {
    return common_button_name;
}
QPushButton* GraphicsButtonLists::get_figure_button() const {
    return add_figure_button;
}
QPushButton* GraphicsButtonLists::get_remove_all_figures_button() const {
    return remove_all_figures_button;
}
QPushButton* GraphicsButtonLists::get_remove_button() const {
    return remove_button;
}
QPushButton* GraphicsButtonLists::get_end_drawing_button() const {
    return end_drawing_button;
}
