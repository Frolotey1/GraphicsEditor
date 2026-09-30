#ifndef INSTRUMENTSLISTSTYLEBRUSHMENU_H
#define INSTRUMENTSLISTSTYLEBRUSHMENU_H
#include "QMenu"
#include "QAction"

class InstrumentsListStyleBrushMenu {
public:
    InstrumentsListStyleBrushMenu();
    QMenu* get_list_style_brush_menu() const;
    QAction* get_reset_brushes_menu() const;
private:
    QMenu* list_style_brush_menu = nullptr;
    QAction* reset_brushes_menu = nullptr;
};

#endif // INSTRUMENTSLISTSTYLEBRUSHMENU_H
