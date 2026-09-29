#ifndef GRAPHICSBUTTONLISTS_H
#define GRAPHICSBUTTONLISTS_H
#include "QGroupBox"
#include "QPushButton"

class GraphicsButtonLists {
public:
    GraphicsButtonLists();
    QGroupBox* get_common_button_name() const;
    QPushButton* get_figure_button() const;
    QPushButton* get_remove_all_figures_button() const;
    QPushButton* get_remove_button() const;
    QPushButton* get_end_drawing_button() const;
private:
    QGroupBox* common_button_name = nullptr;
    QPushButton* add_figure_button = nullptr;
    QPushButton* remove_all_figures_button = nullptr;
    QPushButton* remove_button = nullptr;
    QPushButton* end_drawing_button = nullptr;
};

#endif // GRAPHICSBUTTONLISTS_H
