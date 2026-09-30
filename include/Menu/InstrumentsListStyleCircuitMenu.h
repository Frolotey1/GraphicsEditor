#ifndef INSTRUMENTSLISTSTYLECIRCUITMENU_H
#define INSTRUMENTSLISTSTYLECIRCUITMENU_H
#include "QMenu"
#include "QAction"
#include "QString"

class InstrumentsListStyleCircuitMenu {
public:
    InstrumentsListStyleCircuitMenu();
    QMenu* get_list_style_line_circuit_menu() const;
    QMenu* get_list_style_edge_circuit_menu() const;
    QMenu* get_list_style_join_circuit_menu() const;
    QAction* get_reset_all_styles_this_menu() const;
private:
    QMenu* list_style_line_circuit_menu = nullptr;
    QMenu* list_style_edge_circuit_menu = nullptr;
    QMenu* list_style_join_circuit_menu = nullptr;
    QAction* reset_all_styles_this_menu = nullptr;
};

#endif // INSTRUMENTSLISTSTYLECIRCUITMENU_H
