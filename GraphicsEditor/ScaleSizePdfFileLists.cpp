#include "ScaleSizePdfFileLists.h"

ScaleSizePdfFileLists::ScaleSizePdfFileLists(QToolButton* tool_button) {
    set_menu = new QMenu(tool_button);

    scale_sizes = {"800x600","1000x700","1280x720","1920x1080"};

    for(QString& scale_size : scale_sizes) {
        set_menu->addAction(scale_size);
    }
}
QMenu* ScaleSizePdfFileLists::get_scale_size_menu() const {
    return set_menu;
}
