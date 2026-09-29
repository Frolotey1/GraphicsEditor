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
public:
    BrushOwnColorWindow(QDialog* parent = nullptr);
    QString get_brush_color() const;
private slots:
    void on_button_clicked();
    void on_ok_clicked();
    void on_cancel_clicked();
private:
    QPushButton* create_color_button = nullptr;
    QStatusBar* status = nullptr;
    QColor color;
    QDialogButtonBox* button_box = nullptr;
};

#endif // BRUSHOWNCOLORWINDOW_H
