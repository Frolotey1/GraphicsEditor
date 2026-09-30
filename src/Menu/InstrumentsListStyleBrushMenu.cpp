#include "include/Menu/InstrumentsListStyleBrushMenu.h"

InstrumentsListStyleBrushMenu::InstrumentsListStyleBrushMenu() {
    list_style_brush_menu = new QMenu("Стили");

    list_style_brush_menu->addAction("Горизонтальный");
    list_style_brush_menu->addAction("Вертикальный");
    list_style_brush_menu->addAction("Сплошной");
    list_style_brush_menu->addAction("Нет заливки");

    reset_brushes_menu = new QAction("Сбросить стили");
}
QMenu* InstrumentsListStyleBrushMenu::get_list_style_brush_menu() const {
    return list_style_brush_menu;
}
QAction* InstrumentsListStyleBrushMenu::get_reset_brushes_menu() const {
    return reset_brushes_menu;
}
