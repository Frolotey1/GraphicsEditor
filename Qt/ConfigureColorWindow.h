#ifndef CONFIGURECOLORWINDOW_H
#define CONFIGURECOLORWINDOW_H
#include "QDialog"
#include "QDialogButtonBox"
#include "QColor"
#include "QPushButton"
#include "QVBoxLayout"
#include "QStatusBar"
#include "QList"
#include "QColorDialog"
#include "QBrush"

class ConfigureColorWindow : public QDialog {
    QColor color;
    QPushButton* choose_color_button;
    QStatusBar* status;
    QDialogButtonBox* button_box;
    QString foreground_color;
    QBrush* set_brush;
public:
    ConfigureColorWindow(QDialog* parent = nullptr);
    QString get_background_color() const;
    QString get_foreground_color() const;
private:
    void set_background_color(QColor _color);
    void set_foreground_color(const QColor& configure_color);
private slots:
    void on_choose_clicked();
    void on_ok_clicked();
    void on_cancel_clicked();
};

#endif // CONFIGURECOLORWINDOW_H
