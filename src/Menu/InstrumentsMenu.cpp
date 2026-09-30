#include "include/Menu/InstrumentsMenu.h"

InstrumentsMenu::InstrumentsMenu() {
    ilscm = new InstrumentsListStyleCircuitMenu();
    ilsbm = new InstrumentsListStyleBrushMenu();
    grid_menu = new GridMenu();

    set_brush_menu = new QMenu("Заливка");
    set_brush_menu->addMenu(ilsbm->get_list_style_brush_menu());
    set_brush_menu->addAction(ilsbm->get_reset_brushes_menu());

    set_circuit_menu = new QMenu("Контур");
    set_circuit_menu->addMenu(ilscm->get_list_style_line_circuit_menu());
    set_circuit_menu->addMenu(ilscm->get_list_style_edge_circuit_menu());
    set_circuit_menu->addMenu(ilscm->get_list_style_join_circuit_menu());
    set_circuit_menu->addAction(ilscm->get_reset_all_styles_this_menu());

    set_menu = new QMenu("Инструменты");
    set_menu->addMenu(grid_menu->get_grid_menu());
    set_menu->addMenu(set_circuit_menu);
    set_menu->addMenu(set_brush_menu);
}

QMenu* InstrumentsMenu::get_menu() const {
    return set_menu;
}
QMenu* InstrumentsMenu::get_grid_menu() const {
    return grid_menu->get_grid_menu();
}
QAction* InstrumentsMenu::get_reset_grid_action() const {
    return reset_grid_action;
}
QMenu* InstrumentsMenu::get_circuit_menu() const {
    return set_circuit_menu;
}
QMenu* InstrumentsMenu::get_brush_menu() const {
    return set_brush_menu;
}

