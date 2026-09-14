#ifndef CIRCUITOWNCOLORWINDOW_H
#define CIRCUITOWNCOLORWINDOW_H
#include "QDialog"
#include "QDialogButtonBox"
#include "QColor"
#include "QPushButton"
#include "QColorDialog"
#include "QStatusBar"
#include "QVBoxLayout"
#include "QString"

class CircuitOwnColorWindow : public QDialog {
    QPushButton* create_color_button;
    QStatusBar* status;
    QColor color;
    QDialogButtonBox* button_box;
public:
    CircuitOwnColorWindow(QDialog* parent = nullptr);
    QString get_circuit_color();
private slots:
    void on_button_clicked();
    void on_ok_clicked();
    void on_cancel_clicked();
};

#endif // CIRCUITOWNCOLORWINDOW_H
