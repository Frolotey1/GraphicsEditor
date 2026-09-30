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
public:
    CircuitOwnColorWindow(QDialog* parent = nullptr);
    QString get_circuit_color() const;
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

#endif // CIRCUITOWNCOLORWINDOW_H
