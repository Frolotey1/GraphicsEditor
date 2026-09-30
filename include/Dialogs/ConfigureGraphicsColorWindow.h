#ifndef CONFIGUREGRAPHICSCOLORWINDOW_H
#define CONFIGUREGRAPHICSCOLORWINDOW_H
#include "QDialog"
#include "QDialogButtonBox"
#include "QColor"
#include "QPushButton"
#include "QVBoxLayout"
#include "QStatusBar"
#include "QList"
#include "QColorDialog"
#include "QBrush"

class ConfigureGraphicsColorWindow : public QDialog {
public:
    ConfigureGraphicsColorWindow(QDialog* parent = nullptr);
    QString get_graphics_background_color() const;
private:
    void set_graphics_background_color(QColor& _color);
private slots:
    void on_choose_clicked();
    void on_ok_clicked();
    void on_cancel_clicked();
private:
    QColor color;
    QPushButton* choose_color_button = nullptr;
    QStatusBar* status = nullptr;
    QDialogButtonBox* button_box = nullptr;
    QBrush* set_brush = nullptr;
};

#endif // CONFIGUREGRAPHICSCOLORWINDOW_H
