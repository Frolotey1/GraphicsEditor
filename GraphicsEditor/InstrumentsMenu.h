#ifndef INSTRUMENTSMENU_H
#define INSTRUMENTSMENU_H
#include "QMenu"
#include "QAction"
#include "InstrumentsListStyleCircuitMenu.h"
#include "InstrumentsListStyleBrushMenu.h"
#include "GridMenu.h"

class InstrumentsMenu {
public:
    InstrumentsMenu();
    QMenu* get_menu() const;
    QMenu* get_circuit_menu() const;
    QMenu* get_brush_menu() const;
    QMenu* get_grid_menu() const;
    QAction* get_reset_grid_action() const;
private:
    InstrumentsListStyleCircuitMenu* ilscm = nullptr;
    InstrumentsListStyleBrushMenu* ilsbm = nullptr;
    QMenu* list_grid_menu = nullptr;
    QMenu* list_brush_menu = nullptr;
    QMenu* set_menu = nullptr;
    QMenu* set_circuit_menu = nullptr;
    QMenu* set_brush_menu = nullptr;
    GridMenu* grid_menu = nullptr;
    QAction* reset_grid_action = nullptr;
};

#endif // INSTRUMENTSMENU_H
