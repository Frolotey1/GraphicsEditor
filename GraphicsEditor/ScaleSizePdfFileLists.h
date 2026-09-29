#ifndef SCALESIZEPDFFILELISTS_H
#define SCALESIZEPDFFILELISTS_H
#include "QMenu"
#include "QToolButton"
#include "QList"
#include "QString"

class ScaleSizePdfFileLists {
public:
    ScaleSizePdfFileLists(QToolButton* tool_button);
    QMenu* get_scale_size_menu() const;
private:
    QMenu* set_menu = nullptr;
    QList<QString> scale_sizes;
};

#endif // SCALESIZEPDFFILELISTS_H
