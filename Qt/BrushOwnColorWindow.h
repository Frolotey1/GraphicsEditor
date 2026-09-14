#ifndef BRUSHOWNCOLORWINDOW_H
#define BRUSHOWNCOLORWINDOW_H
#include "QDialog"
#include "QDialogButtonBox"
#include "QVBoxLayout"
#include "QPushButton"
#include "QStatusBar"
#include "QColor"
#include "QVBoxLayout"
#include "QColorDialog"

class BrushOwnColorWindow : public QDialog {
    QPushButton* create_color_button;
    QStatusBar* status;
    QColor color;
    QDialogButtonBox* button_box;
public:
    BrushOwnColorWindow(QDialog* parent = nullptr);
    QString get_brush_color() const;
private slots:
    void on_button_clicked();
    void on_ok_clicked();
    void on_cancel_clicked();
};

#endif // BRUSHOWNCOLORWINDOW_H
