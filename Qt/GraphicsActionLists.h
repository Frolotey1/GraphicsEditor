#ifndef GRAPHICSACTIONLISTS_H
#define GRAPHICSACTIONLISTS_H
#include "QGroupBox"
#include "QPushButton"

class GraphicsActionLists {
    QGroupBox* common_button_name;
    QPushButton* add_figure_button;
    QPushButton* reset_all_figures_button;
    QPushButton* reset_button;
    QPushButton* end_drawing_button;
public:
    GraphicsActionLists();
    QGroupBox* get_common_button_name() const;
    QPushButton* get_figure_button() const;
    QPushButton* get_reset_all_figures_button() const;
    QPushButton* get_reset_button() const;
    QPushButton* get_end_drawing_button() const;
};

#endif // GRAPHICSACTIONLISTS_H
