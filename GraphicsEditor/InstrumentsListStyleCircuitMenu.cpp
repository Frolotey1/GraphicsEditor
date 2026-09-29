#include "InstrumentsListStyleCircuitMenu.h"

InstrumentsListStyleCircuitMenu::InstrumentsListStyleCircuitMenu() {
    list_style_line_circuit_menu = new QMenu("Стили линий");
    list_style_line_circuit_menu->addAction("Сплошная");
    list_style_line_circuit_menu->addAction("Пунктир");
    list_style_line_circuit_menu->addAction("Точки");
    list_style_line_circuit_menu->addAction("Тире-точка");
    list_style_line_circuit_menu->addAction("Тире-две-точки");
    list_style_line_circuit_menu->addAction("Нет контура");

    list_style_edge_circuit_menu = new QMenu("Стили концов");
    list_style_edge_circuit_menu->addAction("Квадратный");
    list_style_edge_circuit_menu->addAction("Плоский");
    list_style_edge_circuit_menu->addAction("Закругленный");

    list_style_join_circuit_menu = new QMenu("Стили соединений");
    list_style_join_circuit_menu->addAction("Срезанный угол");
    list_style_join_circuit_menu->addAction("Острый угол");
    list_style_join_circuit_menu->addAction("Закругленный угол");

    reset_all_styles_this_menu = new QAction("Сбросить все стили");
}
QMenu* InstrumentsListStyleCircuitMenu::get_list_style_line_circuit_menu() const {
    return list_style_line_circuit_menu;
}
QMenu* InstrumentsListStyleCircuitMenu::get_list_style_edge_circuit_menu() const {
    return list_style_edge_circuit_menu;
}
QMenu* InstrumentsListStyleCircuitMenu::get_list_style_join_circuit_menu() const {
    return list_style_join_circuit_menu;
}
QAction* InstrumentsListStyleCircuitMenu::get_reset_all_styles_this_menu() const {
    return reset_all_styles_this_menu;
}
