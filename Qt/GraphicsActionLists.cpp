#include "GraphicsActionLists.h"

GraphicsActionLists::GraphicsActionLists() {
    common_button_name = new QGroupBox("Действия над графикой");
    add_figure_button = new QPushButton("Добавить фигуру");
    reset_all_figures_button = new QPushButton("Сбросить все фигуры");
    reset_button = new QPushButton("Сбросить фигуру");
    end_drawing_button = new QPushButton("Закончить рисование фигур");
}

QGroupBox* GraphicsActionLists::get_common_button_name() const {
    return common_button_name;
}
QPushButton* GraphicsActionLists::get_figure_button() const {
    return add_figure_button;
}
QPushButton* GraphicsActionLists::get_reset_all_figures_button() const {
    return reset_all_figures_button;
}
QPushButton* GraphicsActionLists::get_reset_button() const {
    return reset_button;
}
QPushButton* GraphicsActionLists::get_end_drawing_button() const {
    return end_drawing_button;
}
